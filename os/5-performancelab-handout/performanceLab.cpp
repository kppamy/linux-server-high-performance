#define IDENT 0
#define OP +
// #define OP -
// #define OP OP
// #define OP /
#define data_t int
// #define data_t float

typedef struct
{
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

int get_vec_ele(vec_ptr v, long index, data_t *des)
{
    if (index < 0 || index > v->len)
        return 0;
    *des = v->data[index];
    return 1;
}

long vec_len(vec_ptr v)
{
    return v->len;
}

// CPE:  + 22.68, * 20.02
// -O1:  + 10.12  * 10.12
void combine1(vec_ptr v, data_t *des)
{
    long i;
    *des = IDENT;
    for (i = 0; i < vec_len(v); i++)
    {
        data_t val;
        get_vec_ele(v, i, &val);
        *des = *des OP val;
    }
}

//  decrease function call, optimization blocker
// code motion:  + 7.02,  * 9.03
// -O1:          + 10.12  * 10.12
void combine2(vec_ptr v, data_t *des)
{
    long i;
    *des = IDENT;
    long len = vec_len(v);
    for (i = 0; i < len; i++)
    {
        data_t val;
        get_vec_ele(v, i, &val);
        *des = *des OP val;
    }
}

// decrease function call:
// code motion:                + 7.02,  * 9.03
// direct data acess:          + 7.17   * 9.02
//  no obvious improvement: the high perdictbility of branch==> low penalty
void combine3(vec_ptr v, data_t *des)
{
    long i;
    *des = IDENT;
    long len = vec_len(v);
    data_t *data;
    get_vec_ele(v, 0, data);
    for (i = 0; i < len; i++)
    {
        *des = *des OP data[i];
    }
}

// remove unecessary memory read and write
// direct data acess  with -O2:             + 7.17   * 9.02
// direct data acess  with -O2:             + 1.60   * 3.01
// accumulate result in local variable:     + 1.27   * 3.01
void combine4(vec_ptr v, data_t *des)
{
    long i;
    long len = vec_len(v);
    data_t *data;
    get_vec_ele(v, 0, data);
    data_t acc = IDENT;
    for (i = 0; i < len; i++)
    {
        acc = acc OP data[i];
    }
    *des = acc;
}

// accumulate result in local variable:              + 1.27   * 3.01
// 2*1 unrolling (instruction parallelism, processor):  + 1.01   * 3.01
void combine5(vec_ptr v, data_t *des)
{
    long i;
    long len = vec_len(v);
    long limit = len - 1;
    data_t acc;
    data_t *data;
    get_vec_ele(v, 0, data);
    for (i = 1; i < limit; i += 2)
    {
        acc = (acc OP data[i])OP data[i + 1];
    }

    for (; i < len; i++)
    {
        acc = acc OP data[i];
    }
    *des = acc;
}

// 2*1 unrolling (instruction parallel, processor):  + 1.01   * 3.01
// 2*2 unrolling (instruction parallel, processor):  + 0.81   * 1.51
void combine6(vec_ptr v, data_t *des)
{
    long i;
    long len = vec_len(v);
    long limit = len - 1;
    data_t acc1 = IDENT;
    data_t acc2 = IDENT;
    data_t *data;
    get_vec_ele(v, 0, data);
    for (i = 1; i < limit; i += 2)
    {
        acc1 = acc1 OP data[i];
        acc2 = acc2 OP data[i + 1];
    }

    for (; i < len; i++)
    {
        acc1 = acc1 OP data[i];
    }
    *des = acc1 OP acc2;
}

// 2*2 unrolling (instruction parallel, processor):  + 0.81   * 1.51
// 2*1 unrolling reassociation transformation:       + 1.01   * 1.51
void combine7(vec_ptr v, data_t *des)
{
    long i;
    long len = vec_len(v);
    long limit = len - 1;
    data_t acc;
    data_t *data;
    get_vec_ele(v, 0, data);
    for (i = 1; i < limit; i += 2)
    {
        acc = acc OP(data[i] OP data[i + 1]);
    }

    for (; i < len; i++)
    {
        acc = acc OP data[i];
    }
    *des = acc;
}