/*
 * float.c     floating-point constant support for the Netwide Assembler
 */

// #include "compiler.h"

//#include "nctype.h"

#define DEBUG_FLOAT

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "floats.h"  //  nasm ?????????????? 

/*
 * -----------------
 *  local variables
 * -----------------
 */
static enum float_round rc = 0;     /* rounding control */    //?????? rc = FLOAT_RC_NEAR    =0 

/*
 * -----------
 *  constants
 * -----------
 */

/* "A limb is like a digit but bigger */  
typedef uint32_t fp_limb;  //uint32-t=unsigned int, https://blog.csdn.net/weixin_34133829/article/details/86054430
typedef uint64_t fp_2limb;    //uint64_t unsigned long long 

#define LIMB_BITS       32
#define LIMB_BYTES      4                                        //(LIMB_BITS/8)
#define LIMB_TOP_BIT    ((unsigned int)1 << 31)                  //(LIMB_BITS-1)   32位的无符号整数1=0000 0001H，往左移31位，为8000 0000H 
#define LIMB_MASK       ((unsigned int)(~0))                     //32位的无符号数FFFF FFFFH 
#define LIMB_ALL_BYTES  ((unsigned int)0x01010101)               //32位的无符号数0101 0101H =0000 0001 0000 0001 0000 0001 0000 0001 =16,843,009 
#define LIMB_BYTE(x)    ((x)*LIMB_ALL_BYTES)                     //x*32位的二进制数    0101 0101 H(十六进制) 
/* 112 bits + 64 bits for accuracy + 16 bits for rounding */
#define MANT_LIMBS 6

/* 52 digits fit in 176 bits because 10^53 > 2^176 > 10^52 */
#define MANT_DIGITS 52

/* the format and the argument list depend on MANT_LIMBS */
#define MANT_FMT "%08x %08x %08x %08x %08x %08x"

#define SOME_ARG(a,i) a[i+0], a[i+1], (a)[(i)+2], (a)[(i)+3], (a)[(i)+4], (a)[(i)+5]  //难道作者写复杂了 (a)[(i)+1]

#define MANT_ARG SOME_ARG(mant, 0)

 

/*
 * ---------------------------------------------------------------------------
 *  emit a printf()-like debug message... but only if DEBUG_FLOAT was defined
 * ---------------------------------------------------------------------------
 */

#ifdef DEBUG_FLOAT
#define dprintf(x) printf x
#else
#define dprintf(x) do { } while (0)
#endif

/*
 * ---------------------------------------------------------------------------
 *  multiply
 * ---------------------------------------------------------------------------
 */
static int float_multiply(unsigned int *to, unsigned int *from)     //378,381行调用 
{
    unsigned long long temp[6 * 2];     //  MANT_LIMBS=6
    int i, j;

    /*
     * guaranteed that top bit of 'from' is set -- so we only have
     * to worry about _one_ bit shift to the left
     */
    printf("mul1=%08x %08x %08x %08x %08x %08x\n", SOME_ARG(to, 0));
    printf("%s="MANT_FMT, "mul2", SOME_ARG(from, 0));                   //茴香豆的第二种写法 

    memset(temp, 0, sizeof temp);        //string.h 中的 void memset(void *s,char ch,unsigned n) 将s为首地址的一片连续n个字节内存单元赋值为ch,实质是对temp数组的每个元素初始化赋值为0 
 										 //sizeof 对数据类型取值时，必须要括号，对变量取值时可以不用括号 
    for (i = 0; i < 6; i++) {                     //MANT_LIMBS=6
        for (j = 0; j < 6; j++)  {                // j < MANT_LIMBS; MANT_LIMBS=6
            fp_2limb n;
            n = (fp_2limb) to[i] * (fp_2limb) from[j];
            temp[i + j] += n >>  32;                       //LIMB_BITS=32;
            temp[i + j + 1] += (unsigned int)n;
        }
    }

    for (i = 6 * 2; --i;)  {                    //MANT_LIMBS=6
        temp[i - 1] += temp[i] >> 32;         // temp[i] >> LIMB_BITS
        temp[i] &= 0xffffffff;                  // temp[i] &= LIMB_MASK
    }

    dprintf(("\n%s=" MANT_FMT "_" MANT_FMT "\n", "temp", SOME_ARG(temp, 0),
             SOME_ARG(temp, 6)));                //MANT_LIMBS=6

    if (temp[0] & LIMB_TOP_BIT) {                                           //与 8000 0000H 与 
        for (i = 0; i < 6; i++) {	                                        //6=MANT_LIMBS
            to[i] = temp[i] & LIMB_MASK;                                    // LIMB_MASK为0XffffffffH 
        }
        dprintf(("%s=" MANT_FMT " (%i)\n", "prod", SOME_ARG(to, 0), 0));
        return 0;
    } else {
        for (i = 0; i < 6; i++) {                                          //MANT_LIMBS=6
            to[i] = (temp[i] << 1) + !!(temp[i + 1] & LIMB_TOP_BIT);         //与 8000 0000H 与
        }                                                                     // whether need two !?
        dprintf(("%s=" MANT_FMT " (%i)\n", "prod", SOME_ARG(to, 0), -1));
        return -1;
    }
}

/*
 * ---------------------------------------------------------------------------
 *  convert
 * ---------------------------------------------------------------------------
 */

//将字符串转化为浮点数
//mant uint32_t[6] 6个32字节数组
static bool ieee_flconvert(const char *string, unsigned int *mant,
                           int32_t * exponent)
{
    char digits[MANT_DIGITS];//用于存放每一位数字    //  MANT_DIGITS=52
    char *p, *q, *r;
    unsigned int mult[6], bit;                 //MANT_LIMBS=6
    unsigned int *m;
    int32_t tenpwr; //数值对应的科学计数法中，10的负几次方，例如：0.0001 = 0.1 * 10^-3 tenpwr=-3; 1000 = 0.1 * 10^4 tenpwr=4 
    int32_t twopwr;
    int32_t extratwos;

    
    bool started;
    
    bool seendot;//是否已经出现了小数点
    
    bool warned;//是否超过有效位数的警告

    warned = false;
    p = digits;
    tenpwr = 0;
    started = seendot = false;

    //循环字符串的每个字符
    while (*string && *string != 'E' && *string != 'e') {
        //判断小数点出现的次数，如果大于1次则报错
        if (*string == '.') {
            if (!seendot) {
                seendot = true;
            } else {
                // nasm_nonfatal("too many periods in floating-point constant");
                printf("too many periods in floating-point constant");
                return false;
            }
        }
        //当字符为数字时，进行处理 
        else if (*string >= '0' && *string <= '9') {
            //started表示是否已开始出现非0数字
            //未出现非零数字前
            if (*string == '0' && !started) {
                //还未出现非0数字，说明是0.000类型的小数
                //需要计算数值对应的科学计数法中，10的负几次方
                //例如：0.0001 = 0.1 * 10^-3 tenpwr=-3
                if (seendot) {
                    tenpwr--;
                }
            } 
            //已出现非0数字
            else {
                //设置已出现非0数字
                started = true;
                //当小于指定位数时，逐位填入每个数字
                if (p < digits + sizeof(digits)) {
                    //*string - '0',计算得出每个数字（字符型）对应的实际值（整型）
                    *p++ = *string - '0';
                } else {
                    //超出位数，提示警告信息
                    if (!warned) {
                        /*!
                         *!float-toolong [on] too many digits in floating-point number
                         *!  warns about too many digits in floating-point numbers.
                         */
                        // nasm_warn(WARN_FLOAT_TOOLONG|ERR_PASS2,
                        //            "floating-point constant significand contains "
                        //            "more than %i digits", MANT_DIGITS);
                        printf("floating-point constant significand contains more than %i digits",MANT_DIGITS);  //MANT_DIGITS=52
                        warned = true;
                    }
                }
                //如果未出现小数点，计算10次方的指数，1000 tenpwr=4
                if (!seendot) {
                    tenpwr++;
                }
            }
        }
        //如果是_,则不处理 
        else if (*string == '_') {
            /* do nothing */
        }
        //如果出现其它字符，则报错 
        else {
            // nasm_nonfatalf(ERR_PASS2,
            //                "invalid character in floating-point constant %s: '%c'",
            //                "significand", *string);
            printf("invalid character in floating-point constant %s: '%c'","significand", *string);
            return false;
        }
        string++;
    }

    /*
     * At this point, the memory interval [digits,p) contains a
     * series of decimal digits zzzzzzz, such that our number X
     * satisfies X = 0.zzzzzzz * 10^tenpwr.
     */
    //此时，digits数组中按位存放了从第一个非0数字开始的，每一位的数值
    //digits的有效下标为 [0] ~ [p之前一位],这里p是指针
    q = digits;
    dprintf(("X = 0."));
    while (q < p) {
        dprintf(("%c", *q + '0'));
        q++;
    }
    dprintf((" * 10^%i\n", tenpwr));

    /*
     * Now convert [digits,p) to our internal representation.
     */

    // 开始转换

    //二进制 bit = 1000 0000 0000 0000 0000 0000 0000 0000 
    bit = LIMB_TOP_BIT;                    //8000 0000H 
    dprintf(("bit=%x\n",bit));

    //初始化每一位为0
    for (m = mant; m < mant + 6; m++) {   //MANT_LIMBS=6
        *m = 0;
    }
    m = mant;
    q = digits;
    started = false;
    twopwr = 0;  //二进制计数的指数值，默认为0

    //此时 p 指向digits中最后一位有效数字的后一位
    //     q 指向digits中第一位
    while (m < mant + 6) {                        ////MANT_LIMBS=6
        unsigned int carry = 0;//用于存放进位
        
        //从最后一位p[-1]开始，如果为0，则p--，移除掉后面的0
        while (p > q && !p[-1]) {
            p--;
        }

        //如果全部是0(p==q表示已经移动到了第一位)，直接break
        if (p <= q) {
            break;
        }

        //----------以下为十进制小数转二进制小数--------------
        //小数部分乘以2，取整数部分依次从左往右放在小数点后，直至小数点后为0

        //整体数值*2
        //从末位开始*2 + 进位，
        //只保留个位的值
        //carry存放进位
        for (r = p; r-- > q;) {
            int32_t i;
            i = 2 * *r + carry;
            if (i >= 10) {
                carry = 1;
                i -= 10;
            } else {
                carry = 0;
            }
            *r = i;
        }

        //循环结束后，当前的carry存放的是第一位*2后的进位
        //在没有进位前，不进行二进制的转换，只计算towpwr--,相当于 当前的数 * 2^-towpwr
        //例如：0.05 = 0.1*2^-1 = 0.2*2^-2 = 0.4*2^-3 = 0.8*2^-4 = 1.6*2^-5 
        //towpwr只记录到4，当=5的时候有进位，则开始二进制小数的转换
        //用bit变量来计算当前位是否进位(32位)
        //bit初始化为 1000 0000 0000 0000 0000 0000 0000 0000 
        //当开始二进制转换后每次循环都>>1位（右移一位）
        //如果当前有进位，则与现有数据求或
        //例如：直到第5位有进位时
        //      1000 0000 0000 0000 0000 0000 0000 0000
        //    |      1000 0000 0000 0000 0000 0000 0000
        //    = 1000 1000 0000 0000 0000 0000 0000 0000

        if (carry) {
            *m |= bit;
            //当第一位*2有进位时，started = true,表示开始二进制转换
            //当started为true以后，将不再发生改变，直到当前数据的6个32位处理完毕
            started = true;
        }

        //如果已经开始二进制转换
        if (started) {
            if (bit == 1) {
                //当移动到了最后一位
                //bit重新赋值为1000 0000 0000 0000 0000 0000 0000 0000
                //1000 0000 0000 0000 0000 0000 0000 0000
                //0100 0000 0000 0000 0000 0000 0000 0000
                //0010 0000 0000 0000 0000 0000 0000 0000
                //0001 0000 0000 0000 0000 0000 0000 0000

                //1101 0000 0000 0000 0000 0000 0000 0000
                //开始处理下一个32位
                bit =0x80000000;    //bit = LIMB_TOP_BIT
                m++;
            } else {
                //每次循环，都右移1位
                bit >>= 1;
            }
        }
        //如果还没有开始二进制转换
        else {
            twopwr--;
        }
    }

    //二进制指数 + 十进制指数？？？
    twopwr += tenpwr;

    /*
     * At this point, the 'mant' array contains the first frac-
     * tional places of a base-2^16 real number which when mul-
     * tiplied by 2^twopwr and 5^tenpwr gives X.
     */

    /*
        此时，'mant'数组包含以2^16为基数的实数的第一个小数位
        该实数乘以2^twopwr和5^tenpwr得到X。
    */ 

    dprintf(("X = " MANT_FMT " * 2^%i * 5^%i\n", MANT_ARG, twopwr,
             tenpwr));

    /*
     * Now multiply 'mant' by 5^tenpwr.
     */
    if (tenpwr < 0) {           /* mult = 5^-1 = 0.2 */
        for (m = mult; m < mult + 6 - 1; m++) {                         //MANT_LIMBS=6
            *m = LIMB_BYTE(0xcc);
        }
        mult[6 - 1] = LIMB_BYTE(0xcc)+1;
        extratwos = -2;
        tenpwr = -tenpwr;

        /*
         * If tenpwr was 1000...000b, then it becomes 1000...000b. See
         * the "ANSI C" comment below for more details on that case.
         *
         * Because we already truncated tenpwr to +5000...-5000 inside
         * the exponent parsing code, this shouldn't happen though.
         */
    } else if (tenpwr > 0) {    /* mult = 5^+1 = 5.0 */
        mult[0] = (unsigned int)5 << (32-3); /* 0xA000... */   //LIMB_BITS-3
        for (m = mult + 1; m < mult + 6; m++) {
            *m = 0;
        }
        extratwos = 3;
    } else {
        extratwos = 0;
    }
    while (tenpwr) {
        dprintf(("loop=" MANT_FMT " * 2^%i * 5^%i (%i)\n", MANT_ARG,
                 twopwr, tenpwr, extratwos));
        if (tenpwr & 1) {
            dprintf(("mant*mult\n"));
            twopwr += extratwos + float_multiply(mant, mult);
        }
        dprintf(("mult*mult\n"));
        extratwos = extratwos * 2 + float_multiply(mult, mult);
        tenpwr >>= 1;

        /*
         * In ANSI C, the result of right-shifting a signed integer is
         * considered implementation-specific. To ensure that the loop
         * terminates even if tenpwr was 1000...000b to begin with, we
         * manually clear the MSB, in case a 1 was shifted in.
         *
         * Because we already truncated tenpwr to +5000...-5000 inside
         * the exponent parsing code, this shouldn't matter; neverthe-
         * less it is the right thing to do here.
         */
        tenpwr &= (uint32_t) - 1 >> 1;
    }

    /*
     * At this point, the 'mant' array contains the first frac-
     * tional places of a base-2^16 real number in [0.5,1) that
     * when multiplied by 2^twopwr gives X. Or it contains zero
     * of course. We are done.
     */
    *exponent = twopwr;
    return true;
}

/*
 * ---------------------------------------------------------------------------
 *  operations of specific bits
 * ---------------------------------------------------------------------------
 */

/* Test a single bit */
static int test_bit(const unsigned int *mant, int bit)
{
    return (mant[bit/32] >> (~bit & (32-1))) & 1;    //bit/LIMB_BITS   (LIMB_BITS-1)
}

/*
 * ---------------------------------------------------------------------------
 *  round a mantissa off after i words
 * ---------------------------------------------------------------------------
 */

#define ROUND_COLLECT_BITS                      \
    do {                                        \
        m = mant[i] & (2*bit-1);                \
        for (j = i+1; j < MANT_LIMBS; j++)      \
            m = m | mant[j];                    \
    } while (0)

#define ROUND_ABS_DOWN                          \
    do {                                        \
        mant[i] &= ~(bit-1);                    \
        for (j = i+1; j < MANT_LIMBS; j++)      \
            mant[j] = 0;                        \
        return false;                           \
    } while (0)

#define ROUND_ABS_UP                            \
    do {                                        \
        mant[i] = (mant[i] & ~(bit-1)) + bit;   \
        for (j = i+1; j < MANT_LIMBS; j++)      \
            mant[j] = 0;                        \
        while (i > 0 && !mant[i])               \
            ++mant[--i];                        \
        return !mant[0];                        \
    } while (0)

/*
* 舍入
* 因为表示方法限制了浮点数的范围和精度，所以浮点计算只能近似的表示实数运算。
* 因此，对于值x，我们一般希望采用一种系统的方法，能够得到“最接近的”匹配值x’，
* 这个x'可以用期望的浮点数形式表示出来，这就是舍入的工作。
* minus 是否是负数
* bits  总的位数
*/
static bool ieee_round(bool minus, unsigned int *mant, int bits)
{
    unsigned int m = 0;
    int32_t j;
    int i = bits / 32;                                //     bits / LIMB_BITS
    int p = bits % 32;                         //    bits % LIMB_BITS
    unsigned int bit = 0x80000000 >> p;              //  LIMB_TOP_BIT >> p

    if (rc == FLOAT_RC_NEAR) {
        if (mant[i] & bit) {
            mant[i] &= ~bit;
            ROUND_COLLECT_BITS;
            mant[i] |= bit;
            if (m) {
                ROUND_ABS_UP;
            } else {
                if (test_bit(mant, bits-1)) {
                    ROUND_ABS_UP;
                } else {
                    ROUND_ABS_DOWN;
                }
            }
        } else {
            ROUND_ABS_DOWN;
        }
    } else if (rc == FLOAT_RC_ZERO ||
               rc == (minus ? FLOAT_RC_UP : FLOAT_RC_DOWN)) {
        ROUND_ABS_DOWN;
    } else {
        /* rc == (minus ? FLOAT_RC_DOWN : FLOAT_RC_UP) */
        /* Round toward +/- infinity */
        ROUND_COLLECT_BITS;
        if (m) {
            ROUND_ABS_UP;
        } else {
            ROUND_ABS_DOWN;
        }
    }
    return false;
}


/*
 * Shift a mantissa to the right by i bits.
 * 将尾数向右移动i位
 */
static void ieee_shr(unsigned int *mant, int i)
{
    //mant是一个uint32_t[6]的数组
    unsigned int n, m;
    int j = 0;
    int sr, sl, offs;

    sr = i % 32;                //需要右移的位数       i % LIMB_BITS
    sl = 32-sr;                //前一个元素需要左移的位数
    offs = i/32;               //偏移位数

    if (sr == 0) {
        if (offs)
            for (j = 6-1; j >= offs; j--)
                mant[j] = mant[j-offs];
    } else if (6-1-offs < 0) {                          //MANT_LIMBS=6
        j = 6-1;
    } else {
        //有6个元素需要整体右移i位
        //从最后一个元素开始
        //当前元素右移i位 | 前一个元素左移32-i位，
        //的值赋值给当前元素
        n = mant[6-1-offs] >> sr;
        for (j = 6-1; j > offs; j--) {
            m = mant[j-offs-1];
            mant[j] = (m << sl) | n;
            n = m >> sr;
        }
        mant[j--] = n;
    }
    while (j >= 0)
        mant[j--] = 0;
}

/* Produce standard IEEE formats, with implicit or explicit integer
   bit; this makes the following assumptions:

   - the sign bit is the MSB, followed by the exponent,     //( most significant bit,MSB)
     followed by the integer bit if present.
   - the sign bit plus exponent fit in 16 bits.
   - the exponent bias is 2^(n-1)-1 for an n-bit exponent */

/*
 * The 16- and 128-bit formats are expected to be in IEEE 754r.
 * AMD SSE5 uses the 16-bit format.
 *
 * The 32- and 64-bit formats are the original IEEE 754 formats.
 *
 * The 80-bit format is x87-specific, but widely used.
 *
 * The 8-bit format appears to be the consensus 8-bit floating-point
 * format.  It is apparently used in graphics applications.
 *
 * The b16 format is a 16-bit format with smaller mantissa and larger
 * exponent field.  It is effectively a truncated version of the standard
 * IEEE 32-bit (single) format, but is explicitly supported here in
 * order to support proper rounding.
 *
 * This array must correspond to enum floatize in include/nasm.h.
 * Note that there are some formats which have more than one enum;
 * both need to be listed here with the appropriate offset into the
 * floating-point byte array (use for the floatize operators.)
 *
 * FLOAT_ERR is a value that both represents "invalid format" and the
 * size of this array.
 */

//struct ieee_format {             这个格式在 float.h中定义了 
//    int bytes;                  /* Total bytes */
//    int mantissa;               /* Fractional bits in the mantissa */
//    int explicit;               /* Explicit integer */
//    int exponent;               /* Bits in the exponent */
//    int offset;                 /* Offset into byte array for floatize op */
//   }; 
  
 //给前面flaots.h文件定义的这个数字赋初值 
const struct ieee_format fp_formats[FLOAT_ERR] = {
    {  1,   3, 0,  4, 0 },         /* FLOAT_8 */
    {  2,  10, 0,  5, 0 },         /* FLOAT_16 */
    {  2,   7, 0,  8, 0 },         /* FLOAT_B16 */
    {  4,  23, 0,  8, 0 },         /* FLOAT_32 */
    {  8,  52, 0, 11, 0 },         /* FLOAT_64 */
    { 10,  63, 1, 15, 0 },         /* FLOAT_80M */
    { 10,  63, 1, 15, 8 },         /* FLOAT_80E */
    { 16, 112, 0, 15, 0 },         /* FLOAT_128L */
    { 16, 112, 0, 15, 8 }          /* FLOAT_128H */
};
/* Types of values we can generate */
enum floats {
    FL_ZERO,
    FL_DENORMAL,
    FL_NORMAL,
    FL_INFINITY,
    FL_QNAN,
    FL_SNAN
};

int float_const(const char *str, int s, uint8_t *result, enum floatize ffmt)  // float_const(number, 0, result, ffmt);  char *number="1.05" ,result[4]存放生成的32位浮点数 
{
    const struct ieee_format *fmt = &fp_formats[ffmt];       //ffmt=3    fmt 指向第3行 float 32 参数 
    unsigned int mant[6];      //MANT_LIMBS=6
    int32_t exponent = 0;
    const int32_t expmax = 1 << (fmt->exponent - 1);           // expmax=0000 0080H = 128
    unsigned int one_mask = 0x80000000 >>                       //one_mask=0080 0000H
        ((fmt->exponent+fmt->explicit) % 32);
    const int one_pos = (fmt->exponent+fmt->explicit)/32;      //one_pos=0
    int i;
    int shift;
    enum floats type;
    bool ok;
    const bool minus = s < 0;                                  //minus=false
    const int bits = fmt->bytes * 8;                           //bits=32
    const char *strend;

    // nasm_assert(str[0]);

    ok = ieee_flconvert(str, mant, &exponent);
                                  //返回后，mant[0]=86666666 mant[1]-[5]=6666 6666    exponent=1
    exponent--;

    exponent += expmax - 1;   //exponent=127

    //将得到的数字，整体右移指数+整数的占位位数
    //float32 就是右移8位  mant[0]=0086666 mant[1]-[5]=6666 6666
    ieee_shr(mant, fmt->exponent+fmt->explicit);

    //舍入，取近似值，执行后：只保留32位，即mant[0]=0086 6666  mant[1]-[5]=0000 0000H
    ieee_round(minus, mant, bits);
    
    //这里 mant[0]=0086 6666与 ~one_mask=0111 1111 1111 1111 1111 1111 1111 1111 求&后， mant[0]=0006 6666
    //暂时不知道为什么要这样
    if (!fmt->explicit)                          //  fmt->explicit=0     
        mant[one_pos] = mant[one_pos]&(~one_mask); /* remove explicit one */    //~one_mask=7FFF FFFF

    //将指数合并到数据中，指数左移23位 与mant[0]求或  ,exponent=0000 000F左移23位后的结果为 3f80 0000
    mant[0] = mant[0] | exponent << (32-1 - fmt->exponent);       //mant[0]=3f86666666 =0006 6666 or 3f80 0000
   

    //如果是负数，则第一位置为1 minus ? LIMB_TOP_BIT : 0
    mant[0] =mant[0] | ( minus ? 0x80000000 : 0);        //;  mant[0]=3f86 6666 or 0000 0000  , 3f86 6666=1,065,772,646 

    //LIMB_BYTES = 32/8 = 4 字节
    //result从后往前每次取8位
    for (i = 3; i >= 0; i--)    //3=fmt->bytes-1
        *result++ = mant[i/4] >> (((4-1)-(i%4))*8);     /*这里LIMB_BYTES就是4，i/4=0,共 右移4次：0位、8位、16位、24 位 ,将最低8位的值66 66 86 3f  
                                                        分四次 赋给对应的result[0-3] */ 
    return 1;                   /* success */
}

int main(int argc, char **argv)
{   

    int i=0;
    char *number = "1.05";            //0.105* 10^1
    uint8_t result[4],*p;                //uint8_t 可看成 unsigned char
	p=result;                        //一开始，直接使用result，结果出错，后面 增加了int size=sizeof(f);结果又对了；最后发现应该定义为：uint8_t result[4] 
	
    enum floatize ffmt = FLOAT_32;    //FLOAT_32=3;
    int a;
    a = float_const(number, 0, result, ffmt);          //ffmt=3        598

    printf("a=%d ,result=%x\n",a,result);// output result's address.
    
	for(i=0;i<=3;i++)
        printf("%x ",*(p+i)) ; 
	printf("\n") ;
	   
	/*float f=1.05,*p3;
	unsigned char *p1;
	char *p2;
	p2=&f;                         //如果这样写，有警告，不兼容的指针类型 
    //int size = sizeof(f);
    //printf("size of f %d \n",size);
    
    p=(unsigned char*) &f;
    for(i=0;i<4;i++)
        printf("%x ",*(p+i)) ;  */
    
}
