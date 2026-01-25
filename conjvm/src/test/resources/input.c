static void m68k_op_1010(void) {
    m68ki_exception_1010();
}
static void m68k_op_1111(void) {
    m68ki_exception_1111();
}
static void m68k_op_040fpu0_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68040_fpu_op0();
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_040fpu1_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68040_fpu_op1();
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_abcd_8_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = ((src) & 0x0f) + ((dst) & 0x0f) + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res += 6;
    res += ((src) & 0xf0) + ((dst) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res -= 0xa0;
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xff) | res;
}
static void m68k_op_abcd_8_mm_ax7(void) {
    uint src = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src) & 0x0f) + ((dst) & 0x0f) + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res += 6;
    res += ((src) & 0xf0) + ((dst) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res -= 0xa0;
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_abcd_8_mm_ay7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src) & 0x0f) + ((dst) & 0x0f) + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res += 6;
    res += ((src) & 0xf0) + ((dst) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res -= 0xa0;
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_abcd_8_mm_axy7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src) & 0x0f) + ((dst) & 0x0f) + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res += 6;
    res += ((src) & 0xf0) + ((dst) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res -= 0xa0;
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_abcd_8_mm(void) {
    uint src = OPER_AY_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src) & 0x0f) + ((dst) & 0x0f) + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res += 6;
    res += ((src) & 0xf0) + ((dst) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res -= 0xa0;
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_add_8_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pi7(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_A7_PI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pd7(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_A7_PD_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_a(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_16_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_a(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_32_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_add_8_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_8_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_16_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_add_32_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_adda_16_d(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]))) & 0xffffffff);
}
static void m68k_op_adda_16_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + (sint16)(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]))) & 0xffffffff);
}
static void m68k_op_adda_16_ai(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_AI_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_pi(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_PI_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_pd(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_PD_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_di(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_DI_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_ix(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_IX_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_aw(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AW_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_al(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AL_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_pcdi(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_PCDI_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_pcix(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_PCIX_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_16_i(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(m68ki_read_imm_16());
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_d(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + (m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffffffff);
}
static void m68k_op_adda_32_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffffffff);
}
static void m68k_op_adda_32_ai(void) {
    uint src = OPER_AY_AI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_pi(void) {
    uint src = OPER_AY_PI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_pd(void) {
    uint src = OPER_AY_PD_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_di(void) {
    uint src = OPER_AY_DI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_ix(void) {
    uint src = OPER_AY_IX_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_aw(void) {
    uint src = OPER_AW_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_al(void) {
    uint src = OPER_AL_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_pcdi(void) {
    uint src = OPER_PCDI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_pcix(void) {
    uint src = OPER_PCIX_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_adda_32_i(void) {
    uint src = m68ki_read_imm_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst + src) & 0xffffffff);
}
static void m68k_op_addi_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_addi_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_addi_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_32();
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_addi_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addi_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_addq_8_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_pi7(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_pd7(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_8_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_addq_16_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst + (((m68ki_cpu.ir >> 9) - 1) & 7) + 1) & 0xffffffff);
}
static void m68k_op_addq_16_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_16_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = * r_dst;
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_addq_32_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst + (((m68ki_cpu.ir >> 9) - 1) & 7) + 1) & 0xffffffff);
}
static void m68k_op_addq_32_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addq_32_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_addx_8_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint dst = (( * r_dst) & 0xff);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xff) | res;
}
static void m68k_op_addx_16_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xffff) | res;
}
static void m68k_op_addx_32_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = res;
}
static void m68k_op_addx_8_mm_ax7(void) {
    uint src = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_addx_8_mm_ay7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_addx_8_mm_axy7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_addx_8_mm(void) {
    uint src = OPER_AY_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.v_flag = ((src ^ res) & (dst ^ res));
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_addx_16_mm(void) {
    uint src = OPER_AY_PD_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_addx_32_mm(void) {
    uint src = OPER_AY_PD_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src + dst + ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = (((src ^ res) & (dst ^ res)) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & dst) | (~res & (src | dst))) >> 23);
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_8_er_d(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= ((m68ki_cpu.dar[m68ki_cpu.ir & 7]) | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_ai(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_AI_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pi(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_PI_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pi7(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_A7_PI_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pd(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_PD_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pd7(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_A7_PD_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_di(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_DI_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_ix(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_IX_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_aw(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AW_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_al(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AL_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pcdi(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_PCDI_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_pcix(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_PCIX_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_er_i(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (m68ki_read_imm_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_d(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= ((m68ki_cpu.dar[m68ki_cpu.ir & 7]) | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_ai(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_AI_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_pi(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_PI_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_pd(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_PD_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_di(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_DI_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_ix(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AY_IX_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_aw(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AW_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_al(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_AL_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_pcdi(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_PCDI_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_pcix(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (OPER_PCIX_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_16_er_i(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (m68ki_read_imm_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_d(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_ai(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AY_AI_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_pi(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AY_PI_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_pd(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AY_PD_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_di(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AY_DI_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_ix(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AY_IX_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_aw(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AW_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_al(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_AL_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_pcdi(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_PCDI_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_pcix(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= OPER_PCIX_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_32_er_i(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) &= m68ki_read_imm_32();
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_and_8_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_8_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_16_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_and_32_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_and_32_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_d(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= (m68ki_read_imm_8() | 0xffffff00)) & 0xff);
    m68ki_cpu.n_flag = (m68ki_cpu.not_z_flag);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_andi_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    uint res = src & m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_d(void) {
    m68ki_cpu.not_z_flag = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= (m68ki_read_imm_16() | 0xffff0000)) & 0xffff);
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 8);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_andi_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint res = src & m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_d(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= (m68ki_read_imm_32());
    m68ki_cpu.n_flag = ((m68ki_cpu.not_z_flag) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_andi_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    uint res = src & m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_andi_16_toc(void) {
    m68ki_set_ccr((((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)) & m68ki_read_imm_8());
}
static void m68k_op_andi_16_tos(void) {
    if (m68ki_cpu.s_flag) {
        uint src = m68ki_read_imm_16();;
        m68ki_set_sr((m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))) & src);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_asr_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    if (((src) & 0x80))
        res |= m68ki_shift_8_table[shift];
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
}
static void m68k_op_asr_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    if (((src) & 0x8000))
        res |= m68ki_shift_16_table[shift];
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
}
static void m68k_op_asr_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = * r_dst;
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    if (((src) & 0x80000000))
        res |= m68ki_shift_32_table[shift];
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
}
static void m68k_op_asr_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xff);
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 8) {
            if (((src) & 0x80))
                res |= m68ki_shift_8_table[shift];
            * r_dst = (( * r_dst) & ~0xff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
            m68ki_cpu.n_flag = (res);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        if (((src) & 0x80)) {
            * r_dst |= 0xff;
            m68ki_cpu.c_flag = 0x100;
            m68ki_cpu.x_flag = 0x100;
            m68ki_cpu.n_flag = 0x80;
            m68ki_cpu.not_z_flag = 0xffffffff;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffffff00;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asr_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xffff);
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 16) {
            if (((src) & 0x8000))
                res |= m68ki_shift_16_table[shift];
            * r_dst = (( * r_dst) & ~0xffff) | res;
            m68ki_cpu.c_flag = m68ki_cpu.x_flag = (src >> (shift - 1)) << 8;
            m68ki_cpu.n_flag = ((res) >> 8);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        if (((src) & 0x8000)) {
            * r_dst |= 0xffff;
            m68ki_cpu.c_flag = 0x100;
            m68ki_cpu.x_flag = 0x100;
            m68ki_cpu.n_flag = 0x80;
            m68ki_cpu.not_z_flag = 0xffffffff;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffff0000;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asr_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = * r_dst;
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 32) {
            if (((src) & 0x80000000))
                res |= m68ki_shift_32_table[shift];
            * r_dst = res;
            m68ki_cpu.c_flag = m68ki_cpu.x_flag = (src >> (shift - 1)) << 8;
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        if (((src) & 0x80000000)) {
            * r_dst = 0xffffffff;
            m68ki_cpu.c_flag = 0x100;
            m68ki_cpu.x_flag = 0x100;
            m68ki_cpu.n_flag = 0x80;
            m68ki_cpu.not_z_flag = 0xffffffff;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asr_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asr_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    if (((src) & 0x8000))
        res |= 0x8000;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
}
static void m68k_op_asl_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = ((src << shift) & 0xff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << shift;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    src &= m68ki_shift_8_table[shift + 1];
    m68ki_cpu.v_flag = (!(src == 0 || (src == m68ki_shift_8_table[shift + 1] && shift < 8))) << 7;
}
static void m68k_op_asl_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((src << shift) & 0xffff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> (8 - shift);
    src &= m68ki_shift_16_table[shift + 1];
    m68ki_cpu.v_flag = (!(src == 0 || src == m68ki_shift_16_table[shift + 1])) << 7;
}
static void m68k_op_asl_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = * r_dst;
    uint res = ((src << shift) & 0xffffffff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> (24 - shift);
    src &= m68ki_shift_32_table[shift + 1];
    m68ki_cpu.v_flag = (!(src == 0 || src == m68ki_shift_32_table[shift + 1])) << 7;
}
static void m68k_op_asl_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xff);
    uint res = ((src << shift) & 0xff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 8) {
            * r_dst = (( * r_dst) & ~0xff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << shift;
            m68ki_cpu.n_flag = (res);
            m68ki_cpu.not_z_flag = res;
            src &= m68ki_shift_8_table[shift + 1];
            m68ki_cpu.v_flag = (!(src == 0 || src == m68ki_shift_8_table[shift + 1])) << 7;
            return;
        }
        * r_dst &= 0xffffff00;
        m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((shift == 8 ? src & 1 : 0)) << 8;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = (!(src == 0)) << 7;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asl_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((src << shift) & 0xffff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 16) {
            * r_dst = (( * r_dst) & ~0xffff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = (src << shift) >> 8;
            m68ki_cpu.n_flag = ((res) >> 8);
            m68ki_cpu.not_z_flag = res;
            src &= m68ki_shift_16_table[shift + 1];
            m68ki_cpu.v_flag = (!(src == 0 || src == m68ki_shift_16_table[shift + 1])) << 7;
            return;
        }
        * r_dst &= 0xffff0000;
        m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((shift == 16 ? src & 1 : 0)) << 8;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = (!(src == 0)) << 7;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asl_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = * r_dst;
    uint res = ((src << shift) & 0xffffffff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 32) {
            * r_dst = res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = (src >> (32 - shift)) << 8;
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.not_z_flag = res;
            src &= m68ki_shift_32_table[shift + 1];
            m68ki_cpu.v_flag = (!(src == 0 || src == m68ki_shift_32_table[shift + 1])) << 7;
            return;
        }
        * r_dst = 0;
        m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((shift == 32 ? src & 1 : 0)) << 8;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = (!(src == 0)) << 7;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_asl_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_asl_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    src &= 0xc000;
    m68ki_cpu.v_flag = (!(src == 0 || src == 0xc000)) << 7;
}
static void m68k_op_bhi_8(void) {
    if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bls_8(void) {
    if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bcc_8(void) {
    if ((!(m68ki_cpu.c_flag & 0x100))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bcs_8(void) {
    if ((m68ki_cpu.c_flag & 0x100)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bne_8(void) {
    if (m68ki_cpu.not_z_flag) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_beq_8(void) {
    if ((!m68ki_cpu.not_z_flag)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bvc_8(void) {
    if ((!(m68ki_cpu.v_flag & 0x80))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bvs_8(void) {
    if ((m68ki_cpu.v_flag & 0x80)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bpl_8(void) {
    if ((!(m68ki_cpu.n_flag & 0x80))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bmi_8(void) {
    if ((m68ki_cpu.n_flag & 0x80)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bge_8(void) {
    if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_blt_8(void) {
    if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bgt_8(void) {
    if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_ble_8(void) {
    if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        return;
    }
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
}
static void m68k_op_bhi_16(void) {
    if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bls_16(void) {
    if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bcc_16(void) {
    if ((!(m68ki_cpu.c_flag & 0x100))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bcs_16(void) {
    if ((m68ki_cpu.c_flag & 0x100)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bne_16(void) {
    if (m68ki_cpu.not_z_flag) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_beq_16(void) {
    if ((!m68ki_cpu.not_z_flag)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bvc_16(void) {
    if ((!(m68ki_cpu.v_flag & 0x80))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bvs_16(void) {
    if ((m68ki_cpu.v_flag & 0x80)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bpl_16(void) {
    if ((!(m68ki_cpu.n_flag & 0x80))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bmi_16(void) {
    if ((m68ki_cpu.n_flag & 0x80)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bge_16(void) {
    if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_blt_16(void) {
    if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bgt_16(void) {
    if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_ble_16(void) {
    if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_w);
}
static void m68k_op_bhi_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bls_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bcc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.c_flag & 0x100))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((!(m68ki_cpu.c_flag & 0x100))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bcs_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.c_flag & 0x100)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((m68ki_cpu.c_flag & 0x100)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bne_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.not_z_flag) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if (m68ki_cpu.not_z_flag) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_beq_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!m68ki_cpu.not_z_flag)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((!m68ki_cpu.not_z_flag)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bvc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.v_flag & 0x80))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((!(m68ki_cpu.v_flag & 0x80))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bvs_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.v_flag & 0x80)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((m68ki_cpu.v_flag & 0x80)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bpl_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.n_flag & 0x80))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((!(m68ki_cpu.n_flag & 0x80))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bmi_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.n_flag & 0x80)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((m68ki_cpu.n_flag & 0x80)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bge_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_blt_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bgt_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_ble_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
            uint offset = m68ki_read_imm_32();
            m68ki_cpu.pc -= 4;;
            m68ki_branch_32(offset);
            return;
        }
        m68ki_cpu.pc += 4;
        return;
    } else {
        if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
            ;
            m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
            return;
        }
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_bcc_notake_b);
    }
}
static void m68k_op_bchg_32_r_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst ^= mask;
}
static void m68k_op_bchg_8_r_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_r_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_32_s_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << (m68ki_read_imm_8() & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst ^= mask;
}
static void m68k_op_bchg_8_s_ai(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_pi(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_pi7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_pd(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_pd7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_di(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_ix(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_aw(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bchg_8_s_al(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src ^ mask);
}
static void m68k_op_bclr_32_r_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst &= ~mask;
}
static void m68k_op_bclr_8_r_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_r_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_32_s_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << (m68ki_read_imm_8() & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst &= ~mask;
}
static void m68k_op_bclr_8_s_ai(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_pi(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_pi7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_pd(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_pd7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_di(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_ix(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_aw(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bclr_8_s_al(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src & ~mask);
}
static void m68k_op_bfchg_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint * data = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 mask;
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        mask = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask = ((((offset) < 32 ? (mask) >> (offset) : 0) | ((32 - (offset)) < 32 ? (mask) << (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = (( * data << offset) >> 24);
        m68ki_cpu.not_z_flag = * data & mask;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        * data ^= mask;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfchg_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        m68ki_bitfield_t data;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field ^= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfchg_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        m68ki_bitfield_t data;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field ^= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfchg_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        m68ki_bitfield_t data;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field ^= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfchg_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        m68ki_bitfield_t data;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field ^= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfchg_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        m68ki_bitfield_t data;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field ^= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint * data = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 mask;
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        mask = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask = ((((offset) < 32 ? (mask) >> (offset) : 0) | ((32 - (offset)) < 32 ? (mask) << (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = (( * data << offset) >> 24);
        m68ki_cpu.not_z_flag = * data & mask;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        * data &= ~mask;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint mask_byte = 0;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field &= ~mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint mask_byte = 0;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field &= ~mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint mask_byte = 0;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field &= ~mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint mask_byte = 0;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field &= ~mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfclr_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint mask_byte = 0;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field & mask_base) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field &= ~mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint64 data = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        data = ((((offset) < 32 ? (data) << (offset) : 0) | ((32 - (offset)) < 32 ? (data) >> (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_pcdi();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfexts_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_pcix();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data = (sint32)(data) >> (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint64 data = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        data = ((((offset) < 32 ? (data) << (offset) : 0) | ((32 - (offset)) < 32 ? (data) >> (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= 32 - width;
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_pcdi();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfextu_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint data;
        uint ea = m68ki_get_ea_pcix();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << offset) & 0xffffffff);
        if ((offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.dar[(word2 >> 12) & 7] = data;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint64 data = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint bit;
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        data = ((((offset) < 32 ? (data) << (offset) : 0) | ((32 - (offset)) < 32 ? (data) >> (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= 32 - width;
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = m68ki_get_ea_pcdi();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfffo_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        sint local_offset;
        uint width = word2;
        uint data;
        uint bit;
        uint ea = m68ki_get_ea_pcix();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        local_offset = offset % 8;
        if (local_offset < 0) {
            local_offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        data = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        data = ((data << local_offset) & 0xffffffff);
        if ((local_offset + width) > 32)
            data |= (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << local_offset) >> 8;
        m68ki_cpu.n_flag = ((data) >> 24);
        data >>= (32 - width);
        m68ki_cpu.not_z_flag = data;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        for (bit = 1 << (width - 1); bit && !(data & bit); bit >>= 1)
            offset++;
        m68ki_cpu.dar[(word2 >> 12) & 7] = offset;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint * data = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 mask;
        uint64 insert = m68ki_cpu.dar[(word2 >> 12) & 7];
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        mask = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask = ((((offset) < 32 ? (mask) >> (offset) : 0) | ((32 - (offset)) < 32 ? (mask) << (32 - (offset)) : 0)) & 0xffffffff);
        insert = ((insert << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert) >> 24);
        m68ki_cpu.not_z_flag = insert;
        insert = ((((offset) < 32 ? (insert) >> (offset) : 0) | ((32 - (offset)) < 32 ? (insert) << (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        * data &= ~mask;
        * data |= insert;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint insert_base = m68ki_cpu.dar[(word2 >> 12) & 7];
        m68ki_bitfield_t data;
        uint mask_base;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        insert_base = ((insert_base << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert_base) >> 24);
        m68ki_cpu.not_z_flag = insert_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field = (data.field & ~mask_base) | insert_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint insert_base = m68ki_cpu.dar[(word2 >> 12) & 7];
        m68ki_bitfield_t data;
        uint mask_base;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        insert_base = ((insert_base << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert_base) >> 24);
        m68ki_cpu.not_z_flag = insert_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field = (data.field & ~mask_base) | insert_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint insert_base = m68ki_cpu.dar[(word2 >> 12) & 7];
        m68ki_bitfield_t data;
        uint mask_base;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        insert_base = ((insert_base << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert_base) >> 24);
        m68ki_cpu.not_z_flag = insert_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field = (data.field & ~mask_base) | insert_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint insert_base = m68ki_cpu.dar[(word2 >> 12) & 7];
        m68ki_bitfield_t data;
        uint mask_base;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        insert_base = ((insert_base << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert_base) >> 24);
        m68ki_cpu.not_z_flag = insert_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field = (data.field & ~mask_base) | insert_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfins_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint insert_base = m68ki_cpu.dar[(word2 >> 12) & 7];
        m68ki_bitfield_t data;
        uint mask_base;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        insert_base = ((insert_base << (32 - width)) & 0xffffffff);
        m68ki_cpu.n_flag = ((insert_base) >> 24);
        m68ki_cpu.not_z_flag = insert_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field = (data.field & ~mask_base) | insert_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint * data = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 mask;
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        mask = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask = ((((offset) < 32 ? (mask) >> (offset) : 0) | ((32 - (offset)) < 32 ? (mask) << (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = (( * data << offset) >> 24);
        m68ki_cpu.not_z_flag = * data & mask;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        * data |= mask;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field |= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field |= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field |= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field |= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bfset_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        m68ki_bitfield_t data;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        ea = m68ki_bitfield_patch_ea(ea, offset);
        offset = m68ki_bitfield_patch_offset(offset);
        data = m68ki_load_bitfield(ea, offset, width);
        m68ki_cpu.n_flag = ((data.field) >> 24);
        m68ki_cpu.not_z_flag = data.field & mask_base;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        data.field |= mask_base;
        m68ki_store_bitfield(ea, offset, width, data.field, & data);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint * data = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 mask;
        if (((word2) & 0x00000800))
            offset = m68ki_cpu.dar[offset & 7];
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        offset &= 31;
        width = ((width - 1) & 31) + 1;
        mask = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask = ((((offset) < 32 ? (mask) >> (offset) : 0) | ((32 - (offset)) < 32 ? (mask) << (32 - (offset)) : 0)) & 0xffffffff);
        m68ki_cpu.n_flag = (( * data << offset) >> 24);
        m68ki_cpu.not_z_flag = * data & mask;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = (sint16)(m68ki_read_imm_16());
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_read_imm_32();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_get_ea_pcdi();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bftst_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint offset = (word2 >> 6) & 31;
        uint width = word2;
        uint mask_base;
        uint data_long;
        uint mask_long;
        uint data_byte = 0;
        uint mask_byte = 0;
        uint ea = m68ki_get_ea_pcix();
        if (((word2) & 0x00000800))
            offset = (sint32)(m68ki_cpu.dar[offset & 7]);
        if (((word2) & 0x00000020))
            width = m68ki_cpu.dar[width & 7];
        ea += offset / 8;
        offset %= 8;
        if (offset < 0) {
            offset += 8;
            ea--;
        }
        width = ((width - 1) & 31) + 1;
        mask_base = ((0xffffffff << (32 - width)) & 0xffffffff);
        mask_long = mask_base >> offset;
        data_long = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        m68ki_cpu.n_flag = ((data_long & (0x80000000 >> offset)) << offset) >> 24;
        m68ki_cpu.not_z_flag = data_long & mask_long;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if ((width + offset) > 32) {
            mask_byte = ((mask_base) & 0xff);
            data_byte = m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1);
            m68ki_cpu.not_z_flag |= (data_byte & mask_byte);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bkpt(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        ;
    }
    m68ki_exception_illegal();
}
static void m68k_op_bra_8(void) {
    ;
    m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_bra_16(void) {
    uint offset = m68ki_read_imm_16();
    m68ki_cpu.pc -= 2;;
    m68ki_branch_16(offset);
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_bra_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint offset = m68ki_read_imm_32();
        m68ki_cpu.pc -= 4;;
        m68ki_branch_32(offset);
        if (m68ki_cpu.pc == m68ki_cpu.ppc)
            m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
        return;
    } else {
        ;
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
        if (m68ki_cpu.pc == m68ki_cpu.ppc)
            m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
    }
}
static void m68k_op_bset_32_r_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst |= mask;
}
static void m68k_op_bset_8_r_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_r_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint mask = 1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_32_s_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint mask = 1 << (m68ki_read_imm_8() & 0x1f);
    m68ki_cpu.not_z_flag = * r_dst & mask;
    * r_dst |= mask;
}
static void m68k_op_bset_8_s_ai(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_pi(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_pi7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_pd(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_pd7(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_di(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_ix(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_aw(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bset_8_s_al(void) {
    uint mask = 1 << (m68ki_read_imm_8() & 7);
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_cpu.not_z_flag = src & mask;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, src | mask);
}
static void m68k_op_bsr_8(void) {
    ;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
}
static void m68k_op_bsr_16(void) {
    uint offset = m68ki_read_imm_16();;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_cpu.pc -= 2;
    m68ki_branch_16(offset);
}
static void m68k_op_bsr_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint offset = m68ki_read_imm_32();;
        m68ki_push_32(m68ki_cpu.pc);
        m68ki_cpu.pc -= 4;
        m68ki_branch_32(offset);
        return;
    } else {
        ;
        m68ki_push_32(m68ki_cpu.pc);
        m68ki_branch_8(((m68ki_cpu.ir) & 0xff));
    }
}
static void m68k_op_btst_32_r_d(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x1f));
}
static void m68k_op_btst_8_r_ai(void) {
    m68ki_cpu.not_z_flag = OPER_AY_AI_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pi(void) {
    m68ki_cpu.not_z_flag = OPER_AY_PI_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pi7(void) {
    m68ki_cpu.not_z_flag = OPER_A7_PI_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pd(void) {
    m68ki_cpu.not_z_flag = OPER_AY_PD_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pd7(void) {
    m68ki_cpu.not_z_flag = OPER_A7_PD_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_di(void) {
    m68ki_cpu.not_z_flag = OPER_AY_DI_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_ix(void) {
    m68ki_cpu.not_z_flag = OPER_AY_IX_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_aw(void) {
    m68ki_cpu.not_z_flag = OPER_AW_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_al(void) {
    m68ki_cpu.not_z_flag = OPER_AL_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pcdi(void) {
    m68ki_cpu.not_z_flag = OPER_PCDI_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_pcix(void) {
    m68ki_cpu.not_z_flag = OPER_PCIX_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_8_r_i(void) {
    m68ki_cpu.not_z_flag = m68ki_read_imm_8() & (1 << ((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 7));
}
static void m68k_op_btst_32_s_d(void) {
    m68ki_cpu.not_z_flag = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) & (1 << (m68ki_read_imm_8() & 0x1f));
}
static void m68k_op_btst_8_s_ai(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AY_AI_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pi(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AY_PI_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pi7(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_A7_PI_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pd(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AY_PD_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pd7(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_A7_PD_8() & (1 << bit);
}
static void m68k_op_btst_8_s_di(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AY_DI_8() & (1 << bit);
}
static void m68k_op_btst_8_s_ix(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AY_IX_8() & (1 << bit);
}
static void m68k_op_btst_8_s_aw(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AW_8() & (1 << bit);
}
static void m68k_op_btst_8_s_al(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_AL_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pcdi(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_PCDI_8() & (1 << bit);
}
static void m68k_op_btst_8_s_pcix(void) {
    uint bit = m68ki_read_imm_8() & 7;
    m68ki_cpu.not_z_flag = OPER_PCIX_8() & (1 << bit);
}
static void m68k_op_callm_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = (sint16)(m68ki_read_imm_16());;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = m68ki_read_imm_32();;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = m68ki_get_ea_pcdi();;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_callm_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        uint ea = m68ki_get_ea_pcix();;
        m68ki_cpu.pc += 2;
        (void) ea;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_pi7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_pd7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (sint16)(m68ki_read_imm_16());
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_8_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_read_imm_32();
        uint dest = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xff);;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = (( * compare ^ dest) & (res ^ dest));
        m68ki_cpu.c_flag = (res);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (sint16)(m68ki_read_imm_16());
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_16_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_read_imm_32();
        uint dest = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - (( * compare) & 0xffff);;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        if (m68ki_cpu.not_z_flag)
            *
            compare = (( * compare) & ~0xffff) | dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[(word2 >> 6) & 7]) & 0xffff));
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = (sint16)(m68ki_read_imm_16());
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint ea = m68ki_read_imm_32();
        uint dest = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        uint * compare = & m68ki_cpu.dar[word2 & 7];
        uint res = dest - * compare;;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare ^ dest) & (res ^ dest)) >> 24);
        m68ki_cpu.c_flag = ((( * compare & res) | (~dest & ( * compare | res))) >> 23);
        if (m68ki_cpu.not_z_flag)
            *
            compare = dest;
        else {
            m68ki_remaining_cycles -= (3);
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas2_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_32();
        uint * compare1 = & m68ki_cpu.dar[(word2 >> 16) & 7];
        uint ea1 = m68ki_cpu.dar[(word2 >> 28) & 15];
        uint dest1 = m68ki_read_16_fc(ea1, m68ki_cpu.s_flag | 1);
        uint res1 = dest1 - (( * compare1) & 0xffff);
        uint * compare2 = & m68ki_cpu.dar[word2 & 7];
        uint ea2 = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint dest2 = m68ki_read_16_fc(ea2, m68ki_cpu.s_flag | 1);
        uint res2;;
        m68ki_cpu.n_flag = ((res1) >> 8);
        m68ki_cpu.not_z_flag = ((res1) & 0xffff);
        m68ki_cpu.v_flag = ((( * compare1 ^ dest1) & (res1 ^ dest1)) >> 8);
        m68ki_cpu.c_flag = ((res1) >> 8);
        if ((!m68ki_cpu.not_z_flag)) {
            res2 = dest2 - (( * compare2) & 0xffff);
            m68ki_cpu.n_flag = ((res2) >> 8);
            m68ki_cpu.not_z_flag = ((res2) & 0xffff);
            m68ki_cpu.v_flag = ((( * compare2 ^ dest2) & (res2 ^ dest2)) >> 8);
            m68ki_cpu.c_flag = ((res2) >> 8);
            if ((!m68ki_cpu.not_z_flag)) {
                m68ki_remaining_cycles -= (3);
                m68ki_write_16_fc(ea1, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 22) & 7]);
                m68ki_write_16_fc(ea2, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
                return;
            }
        }
        * compare1 = ((word2) & 0x80000000) ? (uint)(sint16)(dest1) : (( * compare1) & ~0xffff) | dest1;
        * compare2 = ((word2) & 0x00008000) ? (uint)(sint16)(dest2) : (( * compare2) & ~0xffff) | dest2;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cas2_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_32();
        uint * compare1 = & m68ki_cpu.dar[(word2 >> 16) & 7];
        uint ea1 = m68ki_cpu.dar[(word2 >> 28) & 15];
        uint dest1 = m68ki_read_32_fc(ea1, m68ki_cpu.s_flag | 1);
        uint res1 = dest1 - * compare1;
        uint * compare2 = & m68ki_cpu.dar[word2 & 7];
        uint ea2 = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint dest2 = m68ki_read_32_fc(ea2, m68ki_cpu.s_flag | 1);
        uint res2;;
        m68ki_cpu.n_flag = ((res1) >> 24);
        m68ki_cpu.not_z_flag = ((res1) & 0xffffffff);
        m68ki_cpu.v_flag = ((( * compare1 ^ dest1) & (res1 ^ dest1)) >> 24);
        m68ki_cpu.c_flag = ((( * compare1 & res1) | (~dest1 & ( * compare1 | res1))) >> 23);
        if ((!m68ki_cpu.not_z_flag)) {
            res2 = dest2 - * compare2;
            m68ki_cpu.n_flag = ((res2) >> 24);
            m68ki_cpu.not_z_flag = ((res2) & 0xffffffff);
            m68ki_cpu.v_flag = ((( * compare2 ^ dest2) & (res2 ^ dest2)) >> 24);
            m68ki_cpu.c_flag = ((( * compare2 & res2) | (~dest2 & ( * compare2 | res2))) >> 23);
            if ((!m68ki_cpu.not_z_flag)) {
                m68ki_remaining_cycles -= (3);
                m68ki_write_32_fc(ea1, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 22) & 7]);
                m68ki_write_32_fc(ea2, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[(word2 >> 6) & 7]);
                return;
            }
        }
        * compare1 = dest1;
        * compare2 = dest2;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_16_d(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_ai(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AY_AI_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_pi(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AY_PI_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_pd(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AY_PD_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_di(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AY_DI_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_ix(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AY_IX_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_aw(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AW_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_al(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_AL_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_pcdi(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_PCDI_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_pcix(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(OPER_PCIX_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_16_i(void) {
    sint src = (sint16)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
    sint bound = (sint16)(m68ki_read_imm_16());
    m68ki_cpu.not_z_flag = ((src) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    if (src >= 0 && src <= bound) {
        return;
    }
    m68ki_cpu.n_flag = (src < 0) << 7;
    m68ki_exception_trap(6);
}
static void m68k_op_chk_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AY_AI_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AY_PI_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AY_PD_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AY_DI_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AY_IX_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AW_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_AL_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_PCDI_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(OPER_PCIX_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk_32_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        sint src = (sint32)((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]));
        sint bound = (sint32)(m68ki_read_imm_32());
        m68ki_cpu.not_z_flag = ((src) & 0xffffffff);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        if (src >= 0 && src <= bound) {
            return;
        }
        m68ki_cpu.n_flag = (src < 0) << 7;
        m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = m68ki_get_ea_pcdi();
        sint lower_bound = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 2);
        sint upper_bound = m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 2);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = m68ki_get_ea_pcix();
        sint lower_bound = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 2);
        sint upper_bound = m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 2);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        sint lower_bound = (int8) m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int8) m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        sint lower_bound = (int8) m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int8) m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        sint lower_bound = (int8) m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int8) m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = (sint16)(m68ki_read_imm_16());
        sint lower_bound = (int8) m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int8) m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_8_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
        uint ea = m68ki_read_imm_32();
        sint lower_bound = (int8) m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int8) m68ki_read_8_fc(ea + 1, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int8) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = m68ki_get_ea_pcdi();
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 2);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 2);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = m68ki_get_ea_pcix();
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 2);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 2);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = (sint16)(m68ki_read_imm_16());
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_16_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xffff;
        uint ea = m68ki_read_imm_32();
        sint lower_bound = (int16) m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = (int16) m68ki_read_16_fc(ea + 2, m68ki_cpu.s_flag | 1);
        if (!((word2) & 0x00008000))
            compare = (int32)(int16) compare;
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = m68ki_get_ea_pcdi();
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 2);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 2);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = m68ki_get_ea_pcix();
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = (sint16)(m68ki_read_imm_16());
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_chk2cmp2_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        sint compare = m68ki_cpu.dar[(word2 >> 12) & 15];
        uint ea = m68ki_read_imm_32();
        sint lower_bound = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
        sint upper_bound = m68ki_read_32_fc(ea + 4, m68ki_cpu.s_flag | 1);
        m68ki_cpu.not_z_flag = !((upper_bound == compare) || (lower_bound == compare));
        m68ki_cpu.c_flag = (lower_bound <= upper_bound ? compare < lower_bound || compare > upper_bound : compare > upper_bound || compare < lower_bound) << 8;
        if ((m68ki_cpu.c_flag & 0x100) && ((word2) & 0x00000800))
            m68ki_exception_trap(6);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_clr_8_d(void) {
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_d(void) {
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffff0000;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_ai(void) {
    m68ki_write_16_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_pi(void) {
    m68ki_write_16_fc(((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_pd(void) {
    m68ki_write_16_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_di(void) {
    m68ki_write_16_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_ix(void) {
    m68ki_write_16_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_aw(void) {
    m68ki_write_16_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_16_al(void) {
    m68ki_write_16_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_d(void) {
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) = 0;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_ai(void) {
    m68ki_write_32_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_pi(void) {
    m68ki_write_32_fc(((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_pd(void) {
    m68ki_write_32_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_di(void) {
    m68ki_write_32_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_ix(void) {
    m68ki_write_32_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_aw(void) {
    m68ki_write_32_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_clr_32_al(void) {
    m68ki_write_32_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, 0);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.not_z_flag = 0;
}
static void m68k_op_cmp_8_d(void) {
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_ai(void) {
    uint src = OPER_AY_AI_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pi(void) {
    uint src = OPER_AY_PI_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pi7(void) {
    uint src = OPER_A7_PI_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pd(void) {
    uint src = OPER_AY_PD_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pd7(void) {
    uint src = OPER_A7_PD_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_di(void) {
    uint src = OPER_AY_DI_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_ix(void) {
    uint src = OPER_AY_IX_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_aw(void) {
    uint src = OPER_AW_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_al(void) {
    uint src = OPER_AL_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pcdi(void) {
    uint src = OPER_PCDI_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_pcix(void) {
    uint src = OPER_PCIX_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_8_i(void) {
    uint src = m68ki_read_imm_8();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmp_16_d(void) {
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_a(void) {
    uint src = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_ai(void) {
    uint src = OPER_AY_AI_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_pi(void) {
    uint src = OPER_AY_PI_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_pd(void) {
    uint src = OPER_AY_PD_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_di(void) {
    uint src = OPER_AY_DI_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_ix(void) {
    uint src = OPER_AY_IX_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_aw(void) {
    uint src = OPER_AW_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_al(void) {
    uint src = OPER_AL_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_pcdi(void) {
    uint src = OPER_PCDI_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_pcix(void) {
    uint src = OPER_PCIX_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_16_i(void) {
    uint src = m68ki_read_imm_16();
    uint dst = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmp_32_d(void) {
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_a(void) {
    uint src = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_ai(void) {
    uint src = OPER_AY_AI_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_pi(void) {
    uint src = OPER_AY_PI_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_pd(void) {
    uint src = OPER_AY_PD_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_di(void) {
    uint src = OPER_AY_DI_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_ix(void) {
    uint src = OPER_AY_IX_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_aw(void) {
    uint src = OPER_AW_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_al(void) {
    uint src = OPER_AL_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_pcdi(void) {
    uint src = OPER_PCDI_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_pcix(void) {
    uint src = OPER_PCIX_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmp_32_i(void) {
    uint src = m68ki_read_imm_32();
    uint dst = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_d(void) {
    uint src = (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_a(void) {
    uint src = (sint16)(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_ai(void) {
    uint src = (sint16)(OPER_AY_AI_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_pi(void) {
    uint src = (sint16)(OPER_AY_PI_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_pd(void) {
    uint src = (sint16)(OPER_AY_PD_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_di(void) {
    uint src = (sint16)(OPER_AY_DI_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_ix(void) {
    uint src = (sint16)(OPER_AY_IX_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_aw(void) {
    uint src = (sint16)(OPER_AW_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_al(void) {
    uint src = (sint16)(OPER_AL_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_pcdi(void) {
    uint src = (sint16)(OPER_PCDI_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_pcix(void) {
    uint src = (sint16)(OPER_PCIX_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_16_i(void) {
    uint src = (sint16)(m68ki_read_imm_16());
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_d(void) {
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_a(void) {
    uint src = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_ai(void) {
    uint src = OPER_AY_AI_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_pi(void) {
    uint src = OPER_AY_PI_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_pd(void) {
    uint src = OPER_AY_PD_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_di(void) {
    uint src = OPER_AY_DI_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_ix(void) {
    uint src = OPER_AY_IX_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_aw(void) {
    uint src = OPER_AW_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_al(void) {
    uint src = OPER_AL_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_pcdi(void) {
    uint src = OPER_PCDI_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_pcix(void) {
    uint src = OPER_PCIX_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpa_32_i(void) {
    uint src = m68ki_read_imm_32();
    uint dst = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_8_d(void) {
    uint src = m68ki_read_imm_8();
    uint dst = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AY_AI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AY_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_A7_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AY_PD_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_A7_PD_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AY_DI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AY_IX_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AW_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint dst = OPER_AL_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpi_8_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_8();
        uint dst = OPER_PCDI_8();
        uint res = dst - src;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
        m68ki_cpu.c_flag = (res);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpi_8_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_8();
        uint dst = OPER_PCIX_8();
        uint res = dst - src;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = ((res) & 0xff);
        m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
        m68ki_cpu.c_flag = (res);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpi_16_d(void) {
    uint src = m68ki_read_imm_16();
    uint dst = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AY_AI_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AY_PI_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AY_PD_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AY_DI_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AY_IX_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AW_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint dst = OPER_AL_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpi_16_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_16();
        uint dst = OPER_PCDI_16();
        uint res = dst - src;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpi_16_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_16();
        uint dst = OPER_PCIX_16();
        uint res = dst - src;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = ((res) & 0xffff);
        m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
        m68ki_cpu.c_flag = ((res) >> 8);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpi_32_d(void) {
    uint src = m68ki_read_imm_32();
    uint dst = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = dst - src;;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AY_AI_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AY_PI_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AY_PD_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AY_DI_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AY_IX_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AW_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint dst = OPER_AL_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cmpi_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_32();
        uint dst = OPER_PCDI_32();
        uint res = dst - src;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
        m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpi_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = m68ki_read_imm_32();
        uint dst = OPER_PCIX_32();
        uint res = dst - src;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
        m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
        m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_cmpm_8_ax7(void) {
    uint src = OPER_AY_PI_8();
    uint dst = OPER_A7_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpm_8_ay7(void) {
    uint src = OPER_A7_PI_8();
    uint dst = OPER_AX_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpm_8_axy7(void) {
    uint src = OPER_A7_PI_8();
    uint dst = OPER_A7_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpm_8(void) {
    uint src = OPER_AY_PI_8();
    uint dst = OPER_AX_PI_8();
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.c_flag = (res);
}
static void m68k_op_cmpm_16(void) {
    uint src = OPER_AY_PI_16();
    uint dst = OPER_AX_PI_16();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.c_flag = ((res) >> 8);
}
static void m68k_op_cmpm_32(void) {
    uint src = OPER_AY_PI_32();
    uint dst = OPER_AX_PI_32();
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
}
static void m68k_op_cpbcc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        ;
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_cpdbcc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        ;
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_cpgen_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        ;
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_cpscc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        ;
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_cptrapcc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        ;
        m68ki_cpu.pc += 4;
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_dbt_16(void) {
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbf_16(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = (( * r_dst - 1) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    if (res != 0xffff) {
        uint offset = m68ki_read_imm_16();
        m68ki_cpu.pc -= 2;;
        m68ki_branch_16(offset);
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
        return;
    }
    m68ki_cpu.pc += 2;
    m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
}
static void m68k_op_dbhi_16(void) {
    if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbls_16(void) {
    if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbcc_16(void) {
    if ((m68ki_cpu.c_flag & 0x100)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbcs_16(void) {
    if ((!(m68ki_cpu.c_flag & 0x100))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbne_16(void) {
    if ((!m68ki_cpu.not_z_flag)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbeq_16(void) {
    if (m68ki_cpu.not_z_flag) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbvc_16(void) {
    if ((m68ki_cpu.v_flag & 0x80)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbvs_16(void) {
    if ((!(m68ki_cpu.v_flag & 0x80))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbpl_16(void) {
    if ((m68ki_cpu.n_flag & 0x80)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbmi_16(void) {
    if ((!(m68ki_cpu.n_flag & 0x80))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbge_16(void) {
    if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dblt_16(void) {
    if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dbgt_16(void) {
    if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_dble_16(void) {
    if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint res = (( * r_dst - 1) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        if (res != 0xffff) {
            uint offset = m68ki_read_imm_16();
            m68ki_cpu.pc -= 2;;
            m68ki_branch_16(offset);
            m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_noexp);
            return;
        }
        m68ki_cpu.pc += 2;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_dbcc_f_exp);
        return;
    }
    m68ki_cpu.pc += 2;
}
static void m68k_op_divs_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AY_AI_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AY_PI_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AY_PD_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AY_DI_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AY_IX_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AW_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_AL_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_PCDI_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(OPER_PCIX_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divs_16_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    sint src = (sint16)(m68ki_read_imm_16());
    sint quotient;
    sint remainder;
    if (src != 0) {
        if ((uint32) * r_dst == 0x80000000 && src == -1) {
            m68ki_cpu.not_z_flag = 0;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = 0;
            return;
        }
        quotient = (sint32)( * r_dst) / src;
        remainder = (sint32)( * r_dst) % src;
        if (quotient == (sint16)(quotient)) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divu_16_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_16();
    if (src != 0) {
        uint quotient = * r_dst / src;
        uint remainder = * r_dst % src;
        if (quotient < 0x10000) {
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 8);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            * r_dst = ((((quotient) & 0xffff) | (remainder << 16)) & 0xffffffff);
            return;
        }
        m68ki_cpu.v_flag = 0x80;
        return;
    }
    m68ki_exception_trap(5);
}
static void m68k_op_divl_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AY_AI_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AY_PI_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AY_PD_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AY_DI_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AY_IX_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AW_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_AL_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_PCDI_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = OPER_PCIX_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_divl_32_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 divisor = m68ki_read_imm_32();
        uint64 dividend = 0;
        uint64 quotient = 0;
        uint64 remainder = 0;
        if (divisor != 0) {
            if (((word2) & 0x00000400)) {
                dividend = m68ki_cpu.dar[word2 & 7];
                dividend <<= 32;
                dividend |= m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64) dividend / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64) dividend % (sint64)((sint32) divisor));
                    if ((sint64) quotient != (sint64)((sint32) quotient)) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                } else {
                    quotient = dividend / divisor;
                    if (quotient > 0xffffffff) {
                        m68ki_cpu.v_flag = 0x80;
                        return;
                    }
                    remainder = dividend % divisor;
                }
            } else {
                dividend = m68ki_cpu.dar[(word2 >> 12) & 7];
                if (((word2) & 0x00000800)) {
                    quotient = (uint64)((sint64)((sint32) dividend) / (sint64)((sint32) divisor));
                    remainder = (uint64)((sint64)((sint32) dividend) % (sint64)((sint32) divisor));
                } else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
            m68ki_cpu.dar[word2 & 7] = remainder;
            m68ki_cpu.dar[(word2 >> 12) & 7] = quotient;
            m68ki_cpu.n_flag = ((quotient) >> 24);
            m68ki_cpu.not_z_flag = quotient;
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.c_flag = 0;
            return;
        }
        m68ki_exception_trap(5);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_eor_8_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff)) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff)) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eor_32_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= m68ki_read_imm_8()) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    uint res = src ^ m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= m68ki_read_imm_16()) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint res = src ^ m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) ^= m68ki_read_imm_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    uint res = src ^ m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_eori_16_toc(void) {
    m68ki_set_ccr((((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)) ^ m68ki_read_imm_8());
}
static void m68k_op_eori_16_tos(void) {
    if (m68ki_cpu.s_flag) {
        uint src = m68ki_read_imm_16();;
        m68ki_set_sr((m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))) ^ src);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_exg_32_dd(void) {
    uint * reg_a = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint * reg_b = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint tmp = * reg_a;
    * reg_a = * reg_b;
    * reg_b = tmp;
}
static void m68k_op_exg_32_aa(void) {
    uint * reg_a = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint * reg_b = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint tmp = * reg_a;
    * reg_a = * reg_b;
    * reg_b = tmp;
}
static void m68k_op_exg_32_da(void) {
    uint * reg_a = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint * reg_b = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint tmp = * reg_a;
    * reg_a = * reg_b;
    * reg_b = tmp;
}
static void m68k_op_ext_16(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | (( * r_dst) & 0xff) | ((( * r_dst) & 0x80) ? 0xff00 : 0);
    m68ki_cpu.n_flag = (( * r_dst) >> 8);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xffff);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_ext_32(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst) & 0xffff) | ((( * r_dst) & 0x8000) ? 0xffff0000 : 0);
    m68ki_cpu.n_flag = (( * r_dst) >> 24);
    m68ki_cpu.not_z_flag = * r_dst;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_extb_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        * r_dst = (( * r_dst) & 0xff) | ((( * r_dst) & 0x80) ? 0xffffff00 : 0);
        m68ki_cpu.n_flag = (( * r_dst) >> 24);
        m68ki_cpu.not_z_flag = * r_dst;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_illegal(void) {
    m68ki_exception_illegal();
}
static void m68k_op_jmp_32_ai(void) {
    m68ki_jump(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_di(void) {
    m68ki_jump((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())));;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_ix(void) {
    m68ki_jump(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])));;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_aw(void) {
    m68ki_jump((sint16)(m68ki_read_imm_16()));;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_al(void) {
    m68ki_jump(m68ki_read_imm_32());;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_pcdi(void) {
    m68ki_jump(m68ki_get_ea_pcdi());;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jmp_32_pcix(void) {
    m68ki_jump(m68ki_get_ea_pcix());;
    if (m68ki_cpu.pc == m68ki_cpu.ppc)
        m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
}
static void m68k_op_jsr_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_al(void) {
    uint ea = m68ki_read_imm_32();;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_pcdi(void) {
    uint ea = m68ki_get_ea_pcdi();;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_jsr_32_pcix(void) {
    uint ea = m68ki_get_ea_pcix();;
    m68ki_push_32(m68ki_cpu.pc);
    m68ki_jump(ea);
}
static void m68k_op_lea_32_ai(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
}
static void m68k_op_lea_32_di(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
}
static void m68k_op_lea_32_ix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
}
static void m68k_op_lea_32_aw(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(m68ki_read_imm_16());
}
static void m68k_op_lea_32_al(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = m68ki_read_imm_32();
}
static void m68k_op_lea_32_pcdi(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = m68ki_get_ea_pcdi();
}
static void m68k_op_lea_32_pcix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = m68ki_get_ea_pcix();
}
static void m68k_op_link_16_a7(void) {
    (m68ki_cpu.dar + 8)[7] -= 4;
    m68ki_write_32_fc((m68ki_cpu.dar + 8)[7], m68ki_cpu.s_flag | 1, (m68ki_cpu.dar + 8)[7]);
    (m68ki_cpu.dar + 8)[7] = (((m68ki_cpu.dar + 8)[7] + (sint16)(m68ki_read_imm_16())) & 0xffffffff);
}
static void m68k_op_link_16(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    m68ki_push_32( * r_dst);
    * r_dst = (m68ki_cpu.dar + 8)[7];
    (m68ki_cpu.dar + 8)[7] = (((m68ki_cpu.dar + 8)[7] + (sint16)(m68ki_read_imm_16())) & 0xffffffff);
}
static void m68k_op_link_32_a7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        (m68ki_cpu.dar + 8)[7] -= 4;
        m68ki_write_32_fc((m68ki_cpu.dar + 8)[7], m68ki_cpu.s_flag | 1, (m68ki_cpu.dar + 8)[7]);
        (m68ki_cpu.dar + 8)[7] = (((m68ki_cpu.dar + 8)[7] + m68ki_read_imm_32()) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_link_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        m68ki_push_32( * r_dst);
        * r_dst = (m68ki_cpu.dar + 8)[7];
        (m68ki_cpu.dar + 8)[7] = (((m68ki_cpu.dar + 8)[7] + m68ki_read_imm_32()) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_lsr_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = * r_dst;
    uint res = src >> shift;
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = res;
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xff);
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift <= 8) {
            * r_dst = (( * r_dst) & ~0xff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << (9 - shift);
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffffff00;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xffff);
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift <= 16) {
            * r_dst = (( * r_dst) & ~0xffff) | res;
            m68ki_cpu.c_flag = m68ki_cpu.x_flag = (src >> (shift - 1)) << 8;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffff0000;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = * r_dst;
    uint res = src >> shift;
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 32) {
            * r_dst = res;
            m68ki_cpu.c_flag = m68ki_cpu.x_flag = (src >> (shift - 1)) << 8;
            m68ki_cpu.n_flag = 0;
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst = 0;
        m68ki_cpu.x_flag = m68ki_cpu.c_flag = (shift == 32 ? ((src) & 0x80000000) >> 23 : 0);
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsr_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = src >> 1;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = 0;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = ((src << shift) & 0xff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << shift;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((src << shift) & 0xffff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> (8 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = * r_dst;
    uint res = ((src << shift) & 0xffffffff);
    if (shift != 0 && ((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> (24 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xff);
    uint res = ((src << shift) & 0xff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift <= 8) {
            * r_dst = (( * r_dst) & ~0xff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = src << shift;
            m68ki_cpu.n_flag = (res);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffffff00;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((src << shift) & 0xffff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift <= 16) {
            * r_dst = (( * r_dst) & ~0xffff) | res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = (src << shift) >> 8;
            m68ki_cpu.n_flag = ((res) >> 8);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst &= 0xffff0000;
        m68ki_cpu.x_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint src = * r_dst;
    uint res = ((src << shift) & 0xffffffff);
    if (shift != 0) {
        if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004))))
            m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
        if (shift < 32) {
            * r_dst = res;
            m68ki_cpu.x_flag = m68ki_cpu.c_flag = (src >> (32 - shift)) << 8;
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        * r_dst = 0;
        m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((shift == 32 ? src & 1 : 0)) << 8;
        m68ki_cpu.n_flag = 0;
        m68ki_cpu.not_z_flag = 0;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_lsl_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((src << 1) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_move_8_d_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_ai(void) {
    uint res = OPER_AY_AI_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pi(void) {
    uint res = OPER_AY_PI_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pd(void) {
    uint res = OPER_AY_PD_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_di(void) {
    uint res = OPER_AY_DI_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_ix(void) {
    uint res = OPER_AY_IX_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_aw(void) {
    uint res = OPER_AW_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_al(void) {
    uint res = OPER_AL_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_pcix(void) {
    uint res = OPER_PCIX_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_d_i(void) {
    uint res = m68ki_read_imm_8();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_aw(void) {
    uint res = OPER_AW_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_al(void) {
    uint res = OPER_AL_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ai_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_aw(void) {
    uint res = OPER_AW_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_al(void) {
    uint res = OPER_AL_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi7_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_aw(void) {
    uint res = OPER_AW_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_al(void) {
    uint res = OPER_AL_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pi_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) ++);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_aw(void) {
    uint res = OPER_AW_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_al(void) {
    uint res = OPER_AL_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd7_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_aw(void) {
    uint res = OPER_AW_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_al(void) {
    uint res = OPER_AL_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_pd_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_aw(void) {
    uint res = OPER_AW_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_al(void) {
    uint res = OPER_AL_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_di_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_aw(void) {
    uint res = OPER_AW_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_al(void) {
    uint res = OPER_AL_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_ix_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_aw(void) {
    uint res = OPER_AW_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_al(void) {
    uint res = OPER_AL_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_aw_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_ai(void) {
    uint res = OPER_AY_AI_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pi(void) {
    uint res = OPER_AY_PI_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pi7(void) {
    uint res = OPER_A7_PI_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pd(void) {
    uint res = OPER_AY_PD_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pd7(void) {
    uint res = OPER_A7_PD_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_di(void) {
    uint res = OPER_AY_DI_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_ix(void) {
    uint res = OPER_AY_IX_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_aw(void) {
    uint res = OPER_AW_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_al(void) {
    uint res = OPER_AL_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pcdi(void) {
    uint res = OPER_PCDI_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_pcix(void) {
    uint res = OPER_PCIX_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_8_al_i(void) {
    uint res = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_ai(void) {
    uint res = OPER_AY_AI_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_pi(void) {
    uint res = OPER_AY_PI_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_pd(void) {
    uint res = OPER_AY_PD_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_di(void) {
    uint res = OPER_AY_DI_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_ix(void) {
    uint res = OPER_AY_IX_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_aw(void) {
    uint res = OPER_AW_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_al(void) {
    uint res = OPER_AL_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_pcix(void) {
    uint res = OPER_PCIX_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_d_i(void) {
    uint res = m68ki_read_imm_16();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_aw(void) {
    uint res = OPER_AW_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_al(void) {
    uint res = OPER_AL_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ai_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_aw(void) {
    uint res = OPER_AW_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_al(void) {
    uint res = OPER_AL_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pi_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 2) - 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_aw(void) {
    uint res = OPER_AW_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_al(void) {
    uint res = OPER_AL_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_pd_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_aw(void) {
    uint res = OPER_AW_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_al(void) {
    uint res = OPER_AL_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_di_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_aw(void) {
    uint res = OPER_AW_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_al(void) {
    uint res = OPER_AL_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_ix_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_aw(void) {
    uint res = OPER_AW_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_al(void) {
    uint res = OPER_AL_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_aw_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_a(void) {
    uint res = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_ai(void) {
    uint res = OPER_AY_AI_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_pi(void) {
    uint res = OPER_AY_PI_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_pd(void) {
    uint res = OPER_AY_PD_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_di(void) {
    uint res = OPER_AY_DI_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_ix(void) {
    uint res = OPER_AY_IX_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_aw(void) {
    uint res = OPER_AW_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_al(void) {
    uint res = OPER_AL_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_pcdi(void) {
    uint res = OPER_PCDI_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_pcix(void) {
    uint res = OPER_PCIX_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_16_al_i(void) {
    uint res = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_ai(void) {
    uint res = OPER_AY_AI_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_pi(void) {
    uint res = OPER_AY_PI_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_pd(void) {
    uint res = OPER_AY_PD_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_di(void) {
    uint res = OPER_AY_DI_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_ix(void) {
    uint res = OPER_AY_IX_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_aw(void) {
    uint res = OPER_AW_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_al(void) {
    uint res = OPER_AL_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_pcix(void) {
    uint res = OPER_PCIX_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_d_i(void) {
    uint res = m68ki_read_imm_32();
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_aw(void) {
    uint res = OPER_AW_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_al(void) {
    uint res = OPER_AL_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ai_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_aw(void) {
    uint res = OPER_AW_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_al(void) {
    uint res = OPER_AL_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pi_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) += 4) - 4);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_aw(void) {
    uint res = OPER_AW_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_al(void) {
    uint res = OPER_AL_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_pd_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, res & 0xFFFF);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (res >> 16) & 0xFFFF);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_aw(void) {
    uint res = OPER_AW_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_al(void) {
    uint res = OPER_AL_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_di_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_aw(void) {
    uint res = OPER_AW_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_al(void) {
    uint res = OPER_AL_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_ix_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_aw(void) {
    uint res = OPER_AW_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_al(void) {
    uint res = OPER_AL_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_aw_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_a(void) {
    uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_ai(void) {
    uint res = OPER_AY_AI_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_pi(void) {
    uint res = OPER_AY_PI_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_pd(void) {
    uint res = OPER_AY_PD_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_di(void) {
    uint res = OPER_AY_DI_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_ix(void) {
    uint res = OPER_AY_IX_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_aw(void) {
    uint res = OPER_AW_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_al(void) {
    uint res = OPER_AL_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_pcdi(void) {
    uint res = OPER_PCDI_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_pcix(void) {
    uint res = OPER_PCIX_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move_32_al_i(void) {
    uint res = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_movea_16_d(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
}
static void m68k_op_movea_16_a(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
}
static void m68k_op_movea_16_ai(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AY_AI_16());
}
static void m68k_op_movea_16_pi(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AY_PI_16());
}
static void m68k_op_movea_16_pd(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AY_PD_16());
}
static void m68k_op_movea_16_di(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AY_DI_16());
}
static void m68k_op_movea_16_ix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AY_IX_16());
}
static void m68k_op_movea_16_aw(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AW_16());
}
static void m68k_op_movea_16_al(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_AL_16());
}
static void m68k_op_movea_16_pcdi(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_PCDI_16());
}
static void m68k_op_movea_16_pcix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(OPER_PCIX_16());
}
static void m68k_op_movea_16_i(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (sint16)(m68ki_read_imm_16());
}
static void m68k_op_movea_32_d(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
}
static void m68k_op_movea_32_a(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
}
static void m68k_op_movea_32_ai(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AY_AI_32();
}
static void m68k_op_movea_32_pi(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AY_PI_32();
}
static void m68k_op_movea_32_pd(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AY_PD_32();
}
static void m68k_op_movea_32_di(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AY_DI_32();
}
static void m68k_op_movea_32_ix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AY_IX_32();
}
static void m68k_op_movea_32_aw(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AW_32();
}
static void m68k_op_movea_32_al(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_AL_32();
}
static void m68k_op_movea_32_pcdi(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_PCDI_32();
}
static void m68k_op_movea_32_pcix(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = OPER_PCIX_32();
}
static void m68k_op_movea_32_i(void) {
    ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) = m68ki_read_imm_32();
}
static void m68k_op_move_16_frc_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & ~0xffff) | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc(((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_frc_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        m68ki_write_16_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_move_16_toc_d(void) {
    m68ki_set_ccr((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
}
static void m68k_op_move_16_toc_ai(void) {
    m68ki_set_ccr(OPER_AY_AI_16());
}
static void m68k_op_move_16_toc_pi(void) {
    m68ki_set_ccr(OPER_AY_PI_16());
}
static void m68k_op_move_16_toc_pd(void) {
    m68ki_set_ccr(OPER_AY_PD_16());
}
static void m68k_op_move_16_toc_di(void) {
    m68ki_set_ccr(OPER_AY_DI_16());
}
static void m68k_op_move_16_toc_ix(void) {
    m68ki_set_ccr(OPER_AY_IX_16());
}
static void m68k_op_move_16_toc_aw(void) {
    m68ki_set_ccr(OPER_AW_16());
}
static void m68k_op_move_16_toc_al(void) {
    m68ki_set_ccr(OPER_AL_16());
}
static void m68k_op_move_16_toc_pcdi(void) {
    m68ki_set_ccr(OPER_PCDI_16());
}
static void m68k_op_move_16_toc_pcix(void) {
    m68ki_set_ccr(OPER_PCIX_16());
}
static void m68k_op_move_16_toc_i(void) {
    m68ki_set_ccr(m68ki_read_imm_16());
}
static void m68k_op_move_16_frs_d(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & ~0xffff) | (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_ai(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_pi(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_pd(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_di(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_ix(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_aw(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = (sint16)(m68ki_read_imm_16());
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_frs_al(void) {
    if (((m68ki_cpu.cpu_type) == (0x00000001)) || m68ki_cpu.s_flag) {
        uint ea = m68ki_read_imm_32();
        m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_d(void) {
    if (m68ki_cpu.s_flag) {
        m68ki_set_sr((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_ai(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AY_AI_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_pi(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AY_PI_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_pd(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AY_PD_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_di(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AY_DI_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_ix(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AY_IX_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_aw(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AW_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_al(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_AL_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_pcdi(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_PCDI_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_pcix(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = OPER_PCIX_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_16_tos_i(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = m68ki_read_imm_16();;
        m68ki_set_sr(new_sr);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_32_fru(void) {
    if (m68ki_cpu.s_flag) {
        ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) = m68ki_cpu.sp[0];
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_move_32_tou(void) {
    if (m68ki_cpu.s_flag) {
        ;
        m68ki_cpu.sp[0] = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_movec_32_cr(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();;
            switch (word2 & 0xfff) {
            case 0x000:
                m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.sfc;
                return;
            case 0x001:
                m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.dfc;
                return;
            case 0x002:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.cacr;
                    return;
                }
                return;
            case 0x800:
                m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.sp[0];
                return;
            case 0x801:
                m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.vbr;
                return;
            case 0x802:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.caar;
                    return;
                }
                m68ki_exception_illegal();
                break;
            case 0x803:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.m_flag ? m68ki_cpu.dar[15] : m68ki_cpu.sp[6];
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x804:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_cpu.m_flag ? m68ki_cpu.sp[4] : m68ki_cpu.dar[15];
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x003:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x004:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x005:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x006:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x007:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x805:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x806:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x807:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            default:
                m68ki_exception_illegal();
                return;
            }
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_movec_32_rc(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();;
            switch (word2 & 0xfff) {
            case 0x000:
                m68ki_cpu.sfc = m68ki_cpu.dar[(word2 >> 12) & 15] & 7;
                return;
            case 0x001:
                m68ki_cpu.dfc = m68ki_cpu.dar[(word2 >> 12) & 15] & 7;
                return;
            case 0x002:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                        m68ki_cpu.cacr = m68ki_cpu.dar[(word2 >> 12) & 15];
                    } else if (((m68ki_cpu.cpu_type) & ((0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                        m68ki_cpu.cacr = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff1f;
                    } else {
                        m68ki_cpu.cacr = m68ki_cpu.dar[(word2 >> 12) & 15] & 0x0f;
                    }
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x800:
                m68ki_cpu.sp[0] = m68ki_cpu.dar[(word2 >> 12) & 15];
                return;
            case 0x801:
                m68ki_cpu.vbr = m68ki_cpu.dar[(word2 >> 12) & 15];
                return;
            case 0x802:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    m68ki_cpu.caar = m68ki_cpu.dar[(word2 >> 12) & 15];
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x803:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    if (!m68ki_cpu.m_flag) {
                        m68ki_cpu.sp[6] = m68ki_cpu.dar[(word2 >> 12) & 15];
                        return;
                    }
                    m68ki_cpu.dar[15] = m68ki_cpu.dar[(word2 >> 12) & 15];
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x804:
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
                    if (!m68ki_cpu.m_flag) {
                        m68ki_cpu.dar[15] = m68ki_cpu.dar[(word2 >> 12) & 15];
                        return;
                    }
                    m68ki_cpu.sp[4] = m68ki_cpu.dar[(word2 >> 12) & 15];
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x003:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x004:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x005:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x006:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x007:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x805:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x806:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            case 0x807:
                if (((m68ki_cpu.cpu_type) & ((0x00000200) | (0x00000080)))) {
                    return;
                }
                m68ki_exception_illegal();
                return;
            default:
                m68ki_exception_illegal();
                return;
            }
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_movem_16_re_pd(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            ea -= 2;
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[15 - i]) & 0xffff));
            count++;
        }
        ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) = ea;
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_re_ai(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[i]) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_re_di(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[i]) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_re_ix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[i]) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_re_aw(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[i]) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_re_al(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, ((m68ki_cpu.dar[i]) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_32_re_pd(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            ea -= 4;
            m68ki_write_16_fc(ea + 2, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[15 - i] & 0xFFFF);
            m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, (m68ki_cpu.dar[15 - i] >> 16) & 0xFFFF);
            count++;
        }
        ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) = ea;
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_re_ai(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[i]);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_re_di(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[i]);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_re_ix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[i]);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_re_aw(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[i]);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_re_al(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.dar[i]);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_16_er_pi(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
        ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) = ea;
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_pcdi(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_pcdi();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 2)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_pcix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_pcix();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 2)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_ai(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_di(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_ix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_aw(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_16_er_al(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = (sint16)(((m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff));
            ea += 2;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_w);
}
static void m68k_op_movem_32_er_pi(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
        ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) = ea;
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_pcdi(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_pcdi();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 2);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_pcix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_pcix();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 2);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_ai(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_di(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_ix(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_aw(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movem_32_er_al(void) {
    uint i = 0;
    uint register_list = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint count = 0;
    for (; i < 16; i++)
        if (register_list & (1 << i)) {
            m68ki_cpu.dar[i] = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
            ea += 4;
            count++;
        }
    m68ki_remaining_cycles -= (count << m68ki_cpu.cyc_movem_l);
}
static void m68k_op_movep_16_re(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((src >> 8) & 0xff));
    m68ki_write_8_fc(ea += 2, m68ki_cpu.s_flag | 1, ((src) & 0xff));
}
static void m68k_op_movep_32_re(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((src >> 24) & 0xff));
    m68ki_write_8_fc(ea += 2, m68ki_cpu.s_flag | 1, ((src >> 16) & 0xff));
    m68ki_write_8_fc(ea += 2, m68ki_cpu.s_flag | 1, ((src >> 8) & 0xff));
    m68ki_write_8_fc(ea += 2, m68ki_cpu.s_flag | 1, ((src) & 0xff));
}
static void m68k_op_movep_16_er(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst) & ~0xffff) | ((m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1) << 8) + m68ki_read_8_fc(ea + 2, m68ki_cpu.s_flag | 1));
}
static void m68k_op_movep_32_er(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) = (m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1) << 24) + (m68ki_read_8_fc(ea + 2, m68ki_cpu.s_flag | 1) << 16) +
    (m68ki_read_8_fc(ea + 4, m68ki_cpu.s_flag | 1) << 8) + m68ki_read_8_fc(ea + 6, m68ki_cpu.s_flag | 1);
}
static void m68k_op_moves_8_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_pi7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_pd7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (sint16)(m68ki_read_imm_16());;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_8_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_read_imm_32();;
            if (((word2) & 0x00000800)) {
                m68ki_write_8_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint8)(m68ki_read_8_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xff) | m68ki_read_8_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (sint16)(m68ki_read_imm_16());;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_16_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_read_imm_32();;
            if (((word2) & 0x00000800)) {
                m68ki_write_16_fc(ea, m68ki_cpu.dfc, ((m68ki_cpu.dar[(word2 >> 12) & 15]) & 0xffff));
                return;
            }
            if (((word2) & 0x00008000)) {
                (m68ki_cpu.dar + 8)[(word2 >> 12) & 7] = (sint16)(m68ki_read_16_fc(ea, m68ki_cpu.sfc));
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((m68ki_cpu.dar[(word2 >> 12) & 7]) & ~0xffff) | m68ki_read_16_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = (sint16)(m68ki_read_imm_16());;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moves_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.s_flag) {
            uint word2 = m68ki_read_imm_16();
            uint ea = m68ki_read_imm_32();;
            if (((word2) & 0x00000800)) {
                m68ki_write_32_fc(ea, m68ki_cpu.dfc, m68ki_cpu.dar[(word2 >> 12) & 15]);
                if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                    m68ki_remaining_cycles -= (2);
                return;
            }
            m68ki_cpu.dar[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, m68ki_cpu.sfc);
            if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010))))
                m68ki_remaining_cycles -= (2);
            return;
        }
        m68ki_exception_privilege_violation();
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_moveq_32(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) = (sint8)(((m68ki_cpu.ir) & 0xff));
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_move16_32(void) {
    uint16 w2 = m68ki_read_imm_16();
    int ax = m68ki_cpu.ir & 7;
    int ay = (w2 >> 12) & 7;
    m68ki_write_32_fc((m68ki_cpu.dar + 8)[ay], m68ki_cpu.s_flag | 1, m68ki_read_32_fc((m68ki_cpu.dar + 8)[ax], m68ki_cpu.s_flag | 1));
    m68ki_write_32_fc((m68ki_cpu.dar + 8)[ay] + 4, m68ki_cpu.s_flag | 1, m68ki_read_32_fc((m68ki_cpu.dar + 8)[ax] + 4, m68ki_cpu.s_flag | 1));
    m68ki_write_32_fc((m68ki_cpu.dar + 8)[ay] + 8, m68ki_cpu.s_flag | 1, m68ki_read_32_fc((m68ki_cpu.dar + 8)[ax] + 8, m68ki_cpu.s_flag | 1));
    m68ki_write_32_fc((m68ki_cpu.dar + 8)[ay] + 12, m68ki_cpu.s_flag | 1, m68ki_read_32_fc((m68ki_cpu.dar + 8)[ax] + 12, m68ki_cpu.s_flag | 1));
    (m68ki_cpu.dar + 8)[ax] += 16;
    (m68ki_cpu.dar + 8)[ay] += 16;
}
static void m68k_op_muls_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]));
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AY_AI_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AY_PI_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AY_PD_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AY_DI_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AY_IX_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AW_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_AL_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_PCDI_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(OPER_PCIX_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_muls_16_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (sint16)(m68ki_read_imm_16());
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x, f = 0; y; y >>= 1) {
            if ((y & 1) != f) {
                c += 2;
                f = 1 - f;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = ((x * (sint16)((( * r_dst) & 0xffff))) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AY_AI_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AY_PI_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AY_PD_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AY_DI_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AY_IX_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AW_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_AL_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_PCDI_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = OPER_PCIX_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mulu_16_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint x = m68ki_read_imm_16();
    if (((m68ki_cpu.cpu_type) & ((0x00000001) | (0x00000002) | (0x00000004)))) {
        uint c = 0;
        for (uint y = x; y; y >>= 1) {
            if ((y & 1)) {
                c += 2;
            }
        }
        m68ki_remaining_cycles -= (c);
    }
    uint res = x * (( * r_dst) & 0xffff);
    * r_dst = res;
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_mull_32_d(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_ai(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AY_AI_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_pi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AY_PI_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_pd(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AY_PD_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_di(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AY_DI_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_ix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AY_IX_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_aw(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AW_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_al(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_AL_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_PCDI_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = OPER_PCIX_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_mull_32_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint word2 = m68ki_read_imm_16();
        uint64 src = m68ki_read_imm_32();
        uint64 dst = m68ki_cpu.dar[(word2 >> 12) & 7];
        uint64 res;
        m68ki_cpu.c_flag = 0;
        if (((word2) & 0x00000800)) {
            res = (sint64)((sint32) src) * (sint64)((sint32) dst);
            if (!((word2) & 0x00000400)) {
                m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
                m68ki_cpu.n_flag = ((res) >> 24);
                m68ki_cpu.v_flag = ((sint64) res != (sint32) res) << 7;
                m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
                return;
            }
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
            m68ki_cpu.n_flag = ((res) >> 56);
            m68ki_cpu.v_flag = 0;
            m68ki_cpu.dar[word2 & 7] = (res >> 32);
            m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
            return;
        }
        res = src * dst;
        if (!((word2) & 0x00000400)) {
            m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
            m68ki_cpu.n_flag = ((res) >> 24);
            m68ki_cpu.v_flag = (res > 0xffffffff) << 7;
            m68ki_cpu.dar[(word2 >> 12) & 7] = m68ki_cpu.not_z_flag;
            return;
        }
        m68ki_cpu.not_z_flag = ((res) & 0xffffffff) | (res >> 32);
        m68ki_cpu.n_flag = ((res) >> 56);
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.dar[word2 & 7] = (res >> 32);
        m68ki_cpu.dar[(word2 >> 12) & 7] = ((res) & 0xffffffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_nbcd_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        * r_dst = (( * r_dst) & ~0xff) | res;
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_nbcd_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((0x9a - dst - ((m68ki_cpu.x_flag >> 8) & 1)) & 0xff);
    if (res != 0x9a) {
        m68ki_cpu.v_flag = ~res;
        if ((res & 0x0f) == 0xa)
            res = (res & 0xf0) + 0x10;
        res = ((res) & 0xff);
        m68ki_cpu.v_flag &= res;
        m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, ((res) & 0xff));
        m68ki_cpu.not_z_flag |= res;
        m68ki_cpu.c_flag = 0x100;
        m68ki_cpu.x_flag = 0x100;
    } else {
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        m68ki_cpu.x_flag = 0;
    }
    m68ki_cpu.n_flag = (res);
}
static void m68k_op_neg_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - (( * r_dst) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = * r_dst & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_neg_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (res);
    m68ki_cpu.v_flag = src & res;
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - (( * r_dst) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = ( * r_dst & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_neg_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - * r_dst;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = ((( * r_dst & res) | (~0 & ( * r_dst | res))) >> 23);
    m68ki_cpu.v_flag = ( * r_dst & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_neg_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_neg_32_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_negx_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - (( * r_dst) & 0xff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = * r_dst & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xff) | res;
}
static void m68k_op_negx_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = src & res;
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - (( * r_dst) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = ( * r_dst & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xffff) | res;
}
static void m68k_op_negx_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (src & res) >> 8;
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = 0 - (( * r_dst) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((( * r_dst & res) | (~0 & ( * r_dst | res))) >> 23);
    m68ki_cpu.v_flag = ( * r_dst & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = res;
}
static void m68k_op_negx_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_negx_32_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = 0 - ((src) & 0xffffffff) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~0 & (src | res))) >> 23);
    m68ki_cpu.v_flag = (src & res) >> 24;
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_nop(void) {
    ;
}
static void m68k_op_not_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = ((~ * r_dst) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = ((~m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = ((~ * r_dst) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = ((~m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint res = * r_dst = ((~ * r_dst) & 0xffffffff);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_not_32_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = ((~m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffffffff);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_d(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff))) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_ai(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_AI_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pi(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PI_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pi7(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_A7_PI_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pd(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PD_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pd7(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_A7_PD_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_di(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_DI_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_ix(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_IX_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_aw(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AW_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_al(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AL_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pcdi(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCDI_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_pcix(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCIX_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_er_i(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= m68ki_read_imm_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_d(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff))) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_ai(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_AI_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_pi(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PI_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_pd(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PD_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_di(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_DI_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_ix(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_IX_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_aw(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AW_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_al(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AL_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_pcdi(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCDI_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_pcix(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCIX_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_er_i(void) {
    uint res = ((((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= m68ki_read_imm_16())) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_d(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_ai(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_AI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_pi(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_pd(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_PD_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_di(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_DI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_ix(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AY_IX_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_aw(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AW_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_al(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_AL_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_pcdi(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCDI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_pcix(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= OPER_PCIX_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_er_i(void) {
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) |= m68ki_read_imm_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_8_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_16_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_or_32_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint res = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_d(void) {
    uint res = ((((m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= m68ki_read_imm_8())) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    uint res = ((src | m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1)) & 0xff);
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= m68ki_read_imm_16()) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint res = ((src | m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= m68ki_read_imm_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    uint res = src | m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ori_16_toc(void) {
    m68ki_set_ccr((((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8)) | m68ki_read_imm_8());
}
static void m68k_op_ori_16_tos(void) {
    if (m68ki_cpu.s_flag) {
        uint src = m68ki_read_imm_16();;
        m68ki_set_sr((m68ki_cpu.t1_flag | m68ki_cpu.t0_flag | (m68ki_cpu.s_flag << 11) | (m68ki_cpu.m_flag << 11) | m68ki_cpu.int_mask | (((m68ki_cpu.x_flag & 0x100) >> 4) | ((m68ki_cpu.n_flag & 0x80) >> 4) | ((!m68ki_cpu.not_z_flag) << 2) | ((m68ki_cpu.v_flag & 0x80) >> 6) | ((m68ki_cpu.c_flag & 0x100) >> 8))) | src);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_pack_16_rr(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]) + m68ki_read_imm_16();
        uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
        * r_dst = (( * r_dst) & ~0xff) | ((src >> 4) & 0x00f0) | (src & 0x000f);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_pack_16_mm_ax7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint ea_src = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint src = m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1);
        ea_src = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        src = ((src << 8) | m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1)) + m68ki_read_imm_16();
        m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((src >> 4) & 0x00f0) | (src & 0x000f));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_pack_16_mm_ay7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint ea_src = ((m68ki_cpu.dar + 8)[7] -= 2);
        uint src = m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1);
        ea_src = ((m68ki_cpu.dar + 8)[7] -= 2);
        src = ((src << 8) | m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1)) + m68ki_read_imm_16();
        m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7])), m68ki_cpu.s_flag | 1, ((src >> 4) & 0x00f0) | (src & 0x000f));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_pack_16_mm_axy7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint ea_src = ((m68ki_cpu.dar + 8)[7] -= 2);
        uint src = m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1);
        ea_src = ((m68ki_cpu.dar + 8)[7] -= 2);
        src = ((src << 8) | m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1)) + m68ki_read_imm_16();
        m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((src >> 4) & 0x00f0) | (src & 0x000f));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_pack_16_mm(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint ea_src = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        uint src = m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1);
        ea_src = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        src = ((src << 8) | m68ki_read_8_fc(ea_src, m68ki_cpu.s_flag | 1)) + m68ki_read_imm_16();
        m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7])), m68ki_cpu.s_flag | 1, ((src >> 4) & 0x00f0) | (src & 0x000f));
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_pea_32_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_al(void) {
    uint ea = m68ki_read_imm_32();
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_pcdi(void) {
    uint ea = m68ki_get_ea_pcdi();
    m68ki_push_32(ea);
}
static void m68k_op_pea_32_pcix(void) {
    uint ea = m68ki_get_ea_pcix();
    m68ki_push_32(ea);
}
static void m68k_op_pflush_32(void) {
    if ((((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) && (m68ki_cpu.has_pmmu)) {
        fprintf(__stderrp, "68040: unhandled PFLUSH\n");
        return;
    }
    m68ki_exception_1111();
}
static void m68k_op_pmmu_32(void) {
    if ((((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) && (m68ki_cpu.has_pmmu)) {
        m68881_mmu_ops();
    } else {
        m68ki_exception_1111();
    }
}
static void m68k_op_reset(void) {
    if (m68ki_cpu.s_flag) {
        ;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_reset);
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_ror_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint shift = orig_shift & 7;
    uint src = (( * r_dst) & 0xff);
    uint res = ((((src) >> (shift)) | ((src) << (8 - (shift)))) & 0xff);
    if (orig_shift != 0)
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << (9 - orig_shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((((src) >> (shift)) | ((src) << (16 - (shift)))) & 0xffff);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << (9 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint64 src = * r_dst;
    uint res = ((((shift) < 32 ? (src) >> (shift) : 0) | ((32 - (shift)) < 32 ? (src) << (32 - (shift)) : 0)) & 0xffffffff);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << (9 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 7;
    uint src = (( * r_dst) & 0xff);
    uint res = ((((src) >> (shift)) | ((src) << (8 - (shift)))) & 0xff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        * r_dst = (( * r_dst) & ~0xff) | res;
        m68ki_cpu.c_flag = src << (8 - ((shift - 1) & 7));
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 15;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((((src) >> (shift)) | ((src) << (16 - (shift)))) & 0xffff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        m68ki_cpu.c_flag = (src >> ((shift - 1) & 15)) << 8;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 31;
    uint64 src = * r_dst;
    uint res = ((((shift) < 32 ? (src) >> (shift) : 0) | ((32 - (shift)) < 32 ? (src) << (32 - (shift)) : 0)) & 0xffffffff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        * r_dst = res;
        m68ki_cpu.c_flag = (src >> ((shift - 1) & 31)) << 8;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_ror_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((src) >> (1)) | ((src) << (16 - (1)))) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << 8;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint shift = orig_shift & 7;
    uint src = (( * r_dst) & 0xff);
    uint res = ((((src) << (shift)) | ((src) >> (8 - (shift)))) & 0xff);
    if (orig_shift != 0)
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src << orig_shift;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((((src) << (shift)) | ((src) >> (16 - (shift)))) & 0xffff);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> (8 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint64 src = * r_dst;
    uint res = ((((shift) < 32 ? (src) << (shift) : 0) | ((32 - (shift)) < 32 ? (src) >> (32 - (shift)) : 0)) & 0xffffffff);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> (24 - shift);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 7;
    uint src = (( * r_dst) & 0xff);
    uint res = ((((src) << (shift)) | ((src) >> (8 - (shift)))) & 0xff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        if (shift != 0) {
            * r_dst = (( * r_dst) & ~0xff) | res;
            m68ki_cpu.c_flag = src << shift;
            m68ki_cpu.n_flag = (res);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        m68ki_cpu.c_flag = (src & 1) << 8;
        m68ki_cpu.n_flag = (src);
        m68ki_cpu.not_z_flag = src;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = (src);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 15;
    uint src = (( * r_dst) & 0xffff);
    uint res = ((((((src) << (shift)) | ((src) >> (16 - (shift)))) & 0xffff)) & 0xffff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        if (shift != 0) {
            * r_dst = (( * r_dst) & ~0xffff) | res;
            m68ki_cpu.c_flag = (src << shift) >> 8;
            m68ki_cpu.n_flag = ((res) >> 8);
            m68ki_cpu.not_z_flag = res;
            m68ki_cpu.v_flag = 0;
            return;
        }
        m68ki_cpu.c_flag = (src & 1) << 8;
        m68ki_cpu.n_flag = ((src) >> 8);
        m68ki_cpu.not_z_flag = src;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 8);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    uint shift = orig_shift & 31;
    uint64 src = * r_dst;
    uint res = ((((shift) < 32 ? (src) << (shift) : 0) | ((32 - (shift)) < 32 ? (src) >> (32 - (shift)) : 0)) & 0xffffffff);
    if (orig_shift != 0) {
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        * r_dst = res;
        m68ki_cpu.c_flag = (src >> ((32 - shift) & 0x1f)) << 8;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.n_flag = ((src) >> 24);
    m68ki_cpu.not_z_flag = src;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rol_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((((((src) << (1)) | ((src) >> (16 - (1)))) & 0xffff)) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.c_flag = src >> 7;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) >> (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) << (9 - (shift))));
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res;
    res = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (shift))));
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint64 src = * r_dst;
    uint64 res = src | (((uint64)((m68ki_cpu.x_flag >> 8) & 1)) << 32);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    res = (((res) >> (shift)) | ((res) << (33 - (shift))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 24;
    res = ((res) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 9;
        uint src = (( * r_dst) & 0xff);
        uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) >> (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) << (9 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res;
        res = ((res) & 0xff);
        * r_dst = (( * r_dst) & ~0xff) | res;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = ( * r_dst);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xff);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 17;
        uint src = (( * r_dst) & 0xffff);
        uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
        res = ((res) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = (( * r_dst) >> 8);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xffff);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 33;
        uint64 src = * r_dst;
        uint64 res = src | (((uint64)((m68ki_cpu.x_flag >> 8) & 1)) << 32);
        res = (((res) >> (shift)) | ((res) << (33 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 24;
        res = ((res) & 0xffffffff);
        * r_dst = res;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = (( * r_dst) >> 24);
    m68ki_cpu.not_z_flag = * r_dst;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxr_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_8_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xff);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) << (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) >> (9 - (shift))));
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res;
    res = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint src = (( * r_dst) & 0xffff);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (shift))));
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | res;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_32_s(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint shift = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint64 src = * r_dst;
    uint64 res = src | (((uint64)((m68ki_cpu.x_flag >> 8) & 1)) << 32);
    if (shift != 0)
        m68ki_remaining_cycles -= (shift << m68ki_cpu.cyc_shift);
    res = (((res) << (shift)) | ((res) >> (33 - (shift))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 24;
    res = ((res) & 0xffffffff);
    * r_dst = res;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_8_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 9;
        uint src = (( * r_dst) & 0xff);
        uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) << (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 8)) >> (9 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res;
        res = ((res) & 0xff);
        * r_dst = (( * r_dst) & ~0xff) | res;
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = ( * r_dst);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xff);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 17;
        uint src = (( * r_dst) & 0xffff);
        uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (shift)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
        res = ((res) & 0xffff);
        * r_dst = (( * r_dst) & ~0xffff) | res;
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = (( * r_dst) >> 8);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xffff);
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_32_r(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint orig_shift = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]) & 0x3f;
    if (orig_shift != 0) {
        uint shift = orig_shift % 33;
        uint64 src = * r_dst;
        uint64 res = src | (((uint64)((m68ki_cpu.x_flag >> 8) & 1)) << 32);
        res = (((res) << (shift)) | ((res) >> (33 - (shift))));
        m68ki_remaining_cycles -= (orig_shift << m68ki_cpu.cyc_shift);
        m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 24;
        res = ((res) & 0xffffffff);
        * r_dst = res;
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        return;
    }
    m68ki_cpu.c_flag = m68ki_cpu.x_flag;
    m68ki_cpu.n_flag = (( * r_dst) >> 24);
    m68ki_cpu.not_z_flag = * r_dst;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_roxl_16_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = (((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) << (1)) | ((src | (((m68ki_cpu.x_flag >> 8) & 1) << 16)) >> (17 - (1))));
    m68ki_cpu.c_flag = m68ki_cpu.x_flag = res >> 8;
    res = ((res) & 0xffff);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_rtd_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000004) | (0x00000008) | (0x00000010) | (0x00000020) | (0x00000040) | (0x00000200) | (0x00000080)))) {
        uint new_pc = m68ki_pull_32();;
        (m68ki_cpu.dar + 8)[7] = (((m68ki_cpu.dar + 8)[7] + (sint16)(m68ki_read_imm_16())) & 0xffffffff);
        m68ki_jump(new_pc);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_rte_32(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr;
        uint new_pc;
        uint format_word;;;
        if (((m68ki_cpu.cpu_type) == (0x00000001))) {
            new_sr = m68ki_pull_16();
            new_pc = m68ki_pull_32();
            m68ki_jump(new_pc);
            m68ki_set_sr(new_sr);
            m68ki_cpu.instr_mode = 0;
            m68ki_cpu.run_mode = 0;
            return;
        }
        if (((m68ki_cpu.cpu_type) == (0x00000004))) {
            format_word = m68ki_read_16_fc((m68ki_cpu.dar + 8)[7] + 6, m68ki_cpu.s_flag | 1) >> 12;
            if (format_word == 0) {
                new_sr = m68ki_pull_16();
                new_pc = m68ki_pull_32();
                m68ki_fake_pull_16();
                m68ki_jump(new_pc);
                m68ki_set_sr(new_sr);
                m68ki_cpu.instr_mode = 0;
                m68ki_cpu.run_mode = 0;
                return;
            } else if (format_word == 8) {
                new_sr = m68ki_pull_16();
                new_pc = m68ki_pull_32();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_32();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_16();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_fake_pull_32();
                m68ki_jump(new_pc);
                m68ki_set_sr(new_sr);
                m68ki_cpu.instr_mode = 0;
                m68ki_cpu.run_mode = 0;
                return;
            }
            m68ki_cpu.instr_mode = 0;
            m68ki_cpu.run_mode = 0;
            m68ki_exception_format_error();
            return;
        }
        rte_loop:
            format_word = m68ki_read_16_fc((m68ki_cpu.dar + 8)[7] + 6, m68ki_cpu.s_flag | 1) >> 12;
        switch (format_word) {
        case 0:
            new_sr = m68ki_pull_16();
            new_pc = m68ki_pull_32();
            m68ki_fake_pull_16();
            m68ki_jump(new_pc);
            m68ki_set_sr(new_sr);
            m68ki_cpu.instr_mode = 0;
            m68ki_cpu.run_mode = 0;
            return;
        case 1:
            new_sr = m68ki_pull_16();
            m68ki_fake_pull_32();
            m68ki_fake_pull_16();
            m68ki_set_sr_noint(new_sr);
            goto rte_loop;
        case 2:
            new_sr = m68ki_pull_16();
            new_pc = m68ki_pull_32();
            m68ki_fake_pull_16();
            m68ki_fake_pull_32();
            m68ki_jump(new_pc);
            m68ki_set_sr(new_sr);
            m68ki_cpu.instr_mode = 0;
            m68ki_cpu.run_mode = 0;
            return;
        }
        m68ki_cpu.instr_mode = 0;
        m68ki_cpu.run_mode = 0;
        m68ki_exception_format_error();
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_rtm_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010)))) {
        ;;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_rtr_32(void) {
    ;
    m68ki_set_ccr(m68ki_pull_16());
    m68ki_jump(m68ki_pull_32());
}
static void m68k_op_rts_32(void) {
    ;
    m68ki_jump(m68ki_pull_32());
}
static void m68k_op_sbcd_8_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = ((dst) & 0x0f) - ((src) & 0x0f) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res -= 6;
    res += ((dst) & 0xf0) - ((src) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res += 0xa0;
    res = ((res) & 0xff);
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xff) | res;
}
static void m68k_op_sbcd_8_mm_ax7(void) {
    uint src = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((dst) & 0x0f) - ((src) & 0x0f) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res -= 6;
    res += ((dst) & 0xf0) - ((src) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res += 0xa0;
    res = ((res) & 0xff);
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_sbcd_8_mm_ay7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((dst) & 0x0f) - ((src) & 0x0f) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res -= 6;
    res += ((dst) & 0xf0) - ((src) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res += 0xa0;
    res = ((res) & 0xff);
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_sbcd_8_mm_axy7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((dst) & 0x0f) - ((src) & 0x0f) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res -= 6;
    res += ((dst) & 0xf0) - ((src) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res += 0xa0;
    res = ((res) & 0xff);
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_sbcd_8_mm(void) {
    uint src = OPER_AY_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = ((dst) & 0x0f) - ((src) & 0x0f) - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.v_flag = ~res;
    if (res > 9)
        res -= 6;
    res += ((dst) & 0xf0) - ((src) & 0xf0);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res > 0x99) << 8;
    if (m68ki_cpu.c_flag)
        res += 0xa0;
    res = ((res) & 0xff);
    m68ki_cpu.v_flag &= res;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_st_8_d(void) {
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
}
static void m68k_op_st_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_st_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, 0xff);
}
static void m68k_op_sf_8_d(void) {
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sf_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_sf_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, 0);
}
static void m68k_op_shi_8_d(void) {
    if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sls_8_d(void) {
    if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_scc_8_d(void) {
    if ((!(m68ki_cpu.c_flag & 0x100))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_scs_8_d(void) {
    if ((m68ki_cpu.c_flag & 0x100)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sne_8_d(void) {
    if (m68ki_cpu.not_z_flag) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_seq_8_d(void) {
    if ((!m68ki_cpu.not_z_flag)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_svc_8_d(void) {
    if ((!(m68ki_cpu.v_flag & 0x80))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_svs_8_d(void) {
    if ((m68ki_cpu.v_flag & 0x80)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_spl_8_d(void) {
    if ((!(m68ki_cpu.n_flag & 0x80))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_smi_8_d(void) {
    if ((m68ki_cpu.n_flag & 0x80)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sge_8_d(void) {
    if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_slt_8_d(void) {
    if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sgt_8_d(void) {
    if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_sle_8_d(void) {
    if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
        (m68ki_cpu.dar[m68ki_cpu.ir & 7]) |= 0xff;
        m68ki_remaining_cycles -= (m68ki_cpu.cyc_scc_r_true);
        return;
    }
    (m68ki_cpu.dar[m68ki_cpu.ir & 7]) &= 0xffffff00;
}
static void m68k_op_shi_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_shi_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, ((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sls_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sls_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, ((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_scc_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scc_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.c_flag & 0x100)) ? 0xff : 0);
}
static void m68k_op_scs_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_scs_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (m68ki_cpu.c_flag & 0x100) ? 0xff : 0);
}
static void m68k_op_sne_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_sne_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag ? 0xff : 0);
}
static void m68k_op_seq_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_seq_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (!m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_svc_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svc_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.v_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_svs_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_svs_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (m68ki_cpu.v_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_spl_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_spl_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (!(m68ki_cpu.n_flag & 0x80)) ? 0xff : 0);
}
static void m68k_op_smi_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_smi_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (m68ki_cpu.n_flag & 0x80) ? 0xff : 0);
}
static void m68k_op_sge_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_sge_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) ? 0xff : 0);
}
static void m68k_op_slt_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_slt_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, ((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) ? 0xff : 0);
}
static void m68k_op_sgt_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sgt_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag) ? 0xff : 0);
}
static void m68k_op_sle_8_ai(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_pi(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_pi7(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[7] += 2) - 2), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_pd(void) {
    m68ki_write_8_fc((--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_pd7(void) {
    m68ki_write_8_fc(((m68ki_cpu.dar + 8)[7] -= 2), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_di(void) {
    m68ki_write_8_fc((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16())), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_ix(void) {
    m68ki_write_8_fc(m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_aw(void) {
    m68ki_write_8_fc((sint16)(m68ki_read_imm_16()), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_sle_8_al(void) {
    m68ki_write_8_fc(m68ki_read_imm_32(), m68ki_cpu.s_flag | 1, (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)) ? 0xff : 0);
}
static void m68k_op_stop(void) {
    if (m68ki_cpu.s_flag) {
        uint new_sr = m68ki_read_imm_16();;
        m68ki_cpu.stopped |= 1;
        m68ki_set_sr(new_sr);
        if (m68ki_remaining_cycles >= m68ki_cpu.cyc_instruction[m68ki_cpu.ir])
            m68ki_remaining_cycles = m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
        else
            m68ki_remaining_cycles %= m68ki_cpu.cyc_instruction[m68ki_cpu.ir];
        return;
    }
    m68ki_exception_privilege_violation();
}
static void m68k_op_sub_8_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pi7(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_A7_PI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pd7(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_A7_PD_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_a(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_16_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_a(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_ai(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_AI_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_pi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PI_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_pd(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_PD_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_di(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_DI_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_ix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AY_IX_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_aw(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AW_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_al(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_AL_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_pcdi(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCDI_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_pcix(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = OPER_PCIX_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_32_er_i(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = m68ki_read_imm_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_sub_8_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_8_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xff);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_16_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (((m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7])) & 0xffff);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_pi(void) {
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_pd(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_sub_32_re_al(void) {
    uint ea = m68ki_read_imm_32();
    uint src = (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_suba_16_d(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - (sint16)((m68ki_cpu.dar[m68ki_cpu.ir & 7]))) & 0xffffffff);
}
static void m68k_op_suba_16_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - (sint16)(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]))) & 0xffffffff);
}
static void m68k_op_suba_16_ai(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_AI_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_pi(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_PI_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_pd(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_PD_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_di(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_DI_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_ix(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AY_IX_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_aw(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AW_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_al(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_AL_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_pcdi(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_PCDI_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_pcix(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(OPER_PCIX_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_16_i(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (sint16)(m68ki_read_imm_16());
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_d(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - (m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffffffff);
}
static void m68k_op_suba_32_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7])) & 0xffffffff);
}
static void m68k_op_suba_32_ai(void) {
    uint src = OPER_AY_AI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_pi(void) {
    uint src = OPER_AY_PI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_pd(void) {
    uint src = OPER_AY_PD_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_di(void) {
    uint src = OPER_AY_DI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_ix(void) {
    uint src = OPER_AY_IX_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_aw(void) {
    uint src = OPER_AW_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_al(void) {
    uint src = OPER_AL_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_pcdi(void) {
    uint src = OPER_PCDI_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_pcix(void) {
    uint src = OPER_PCIX_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_suba_32_i(void) {
    uint src = m68ki_read_imm_32();
    uint * r_dst = & ((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]);
    * r_dst = (( * r_dst - src) & 0xffffffff);
}
static void m68k_op_subi_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_8();
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_subi_8_ai(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_pi(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_pi7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_pd(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_pd7(void) {
    uint src = m68ki_read_imm_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_di(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_ix(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_aw(void) {
    uint src = m68ki_read_imm_8();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_8_al(void) {
    uint src = m68ki_read_imm_8();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_16();
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_subi_16_ai(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_pi(void) {
    uint src = m68ki_read_imm_16();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_pd(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_di(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_ix(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_aw(void) {
    uint src = m68ki_read_imm_16();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_16_al(void) {
    uint src = m68ki_read_imm_16();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = m68ki_read_imm_32();
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_subi_32_ai(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_pi(void) {
    uint src = m68ki_read_imm_32();
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_pd(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_di(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_ix(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_aw(void) {
    uint src = m68ki_read_imm_32();
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subi_32_al(void) {
    uint src = m68ki_read_imm_32();
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    * r_dst = (( * r_dst) & ~0xff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_subq_8_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_pi7(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_pd7(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_8_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = ((res) & 0xff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    * r_dst = (( * r_dst) & ~0xffff) | m68ki_cpu.not_z_flag;
}
static void m68k_op_subq_16_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst - ((((m68ki_cpu.ir >> 9) - 1) & 7) + 1)) & 0xffffffff);
}
static void m68k_op_subq_16_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 2) - 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_16_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = ((res) & 0xffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint dst = * r_dst;
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    * r_dst = m68ki_cpu.not_z_flag;
}
static void m68k_op_subq_32_a(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    * r_dst = (( * r_dst - ((((m68ki_cpu.ir >> 9) - 1) & 7) + 1)) & 0xffffffff);
}
static void m68k_op_subq_32_ai(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_pi(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = ((((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) += 4) - 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_pd(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_di(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_ix(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_aw(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subq_32_al(void) {
    uint src = (((m68ki_cpu.ir >> 9) - 1) & 7) + 1;
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src;
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = ((res) & 0xffffffff);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, m68ki_cpu.not_z_flag);
}
static void m68k_op_subx_8_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    uint dst = (( * r_dst) & 0xff);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xff) | res;
}
static void m68k_op_subx_16_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    uint dst = (( * r_dst) & 0xffff);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = (( * r_dst) & ~0xffff) | res;
}
static void m68k_op_subx_32_rr(void) {
    uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
    uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    uint dst = * r_dst;
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    * r_dst = res;
}
static void m68k_op_subx_8_mm_ax7(void) {
    uint src = OPER_AY_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_subx_8_mm_ay7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_subx_8_mm_axy7(void) {
    uint src = OPER_A7_PD_8();
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_subx_8_mm(void) {
    uint src = OPER_AY_PD_8();
    uint ea = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (res);
    m68ki_cpu.v_flag = ((src ^ dst) & (res ^ dst));
    res = ((res) & 0xff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_subx_16_mm(void) {
    uint src = OPER_AY_PD_16();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 2);
    uint dst = m68ki_read_16_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = ((res) >> 8);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 8);
    res = ((res) & 0xffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_16_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_subx_32_mm(void) {
    uint src = OPER_AY_PD_32();
    uint ea = (((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]) -= 4);
    uint dst = m68ki_read_32_fc(ea, m68ki_cpu.s_flag | 1);
    uint res = dst - src - ((m68ki_cpu.x_flag >> 8) & 1);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.x_flag = m68ki_cpu.c_flag = (((src & res) | (~dst & (src | res))) >> 23);
    m68ki_cpu.v_flag = (((src ^ dst) & (res ^ dst)) >> 24);
    res = ((res) & 0xffffffff);
    m68ki_cpu.not_z_flag |= res;
    m68ki_write_32_fc(ea, m68ki_cpu.s_flag | 1, res);
}
static void m68k_op_swap_32(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    m68ki_cpu.not_z_flag = (( * r_dst << 16) & 0xffffffff);
    * r_dst = ( * r_dst >> 16) | m68ki_cpu.not_z_flag;
    m68ki_cpu.not_z_flag = * r_dst;
    m68ki_cpu.n_flag = (( * r_dst) >> 24);
    m68ki_cpu.c_flag = 0;
    m68ki_cpu.v_flag = 0;
}
static void m68k_op_tas_8_d(void) {
    uint * r_dst = & (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    m68ki_cpu.not_z_flag = (( * r_dst) & 0xff);
    m68ki_cpu.n_flag = ( * r_dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    * r_dst |= 0x80;
}
static void m68k_op_tas_8_ai(void) {
    uint ea = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_pi(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) ++);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_pi7(void) {
    uint ea = (((m68ki_cpu.dar + 8)[7] += 2) - 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_pd(void) {
    uint ea = (--((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_pd7(void) {
    uint ea = ((m68ki_cpu.dar + 8)[7] -= 2);
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_di(void) {
    uint ea = (((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]) + (sint16)(m68ki_read_imm_16()));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_ix(void) {
    uint ea = m68ki_get_ea_ix(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_aw(void) {
    uint ea = (sint16)(m68ki_read_imm_16());
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_tas_8_al(void) {
    uint ea = m68ki_read_imm_32();
    uint dst = m68ki_read_8_fc(ea, m68ki_cpu.s_flag | 1);
    uint allow_writeback;
    m68ki_cpu.not_z_flag = dst;
    m68ki_cpu.n_flag = (dst);
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
    allow_writeback = 1;
    if (allow_writeback == 1) m68ki_write_8_fc(ea, m68ki_cpu.s_flag | 1, dst | 0x80);
}
static void m68k_op_trap(void) {
    m68ki_exception_trapN(32 + (m68ki_cpu.ir & 0xf));
}
static void m68k_op_trapt(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapt_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapt_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapf(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapf_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapf_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traphi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapls(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcc(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.c_flag & 0x100)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcs(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.c_flag & 0x100))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapne(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (m68ki_cpu.not_z_flag)
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapeq(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!m68ki_cpu.not_z_flag))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvc(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.v_flag & 0x80)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvs(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.v_flag & 0x80))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trappl(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!(m68ki_cpu.n_flag & 0x80)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapmi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((m68ki_cpu.n_flag & 0x80))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapge(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traplt(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapgt(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traple(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag)))
            m68ki_exception_trap(7);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traphi_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapls_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcc_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((!(m68ki_cpu.c_flag & 0x100))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcs_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((m68ki_cpu.c_flag & 0x100)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapne_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if (m68ki_cpu.not_z_flag) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapeq_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((!m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvc_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((!(m68ki_cpu.v_flag & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvs_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((m68ki_cpu.v_flag & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trappl_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((!(m68ki_cpu.n_flag & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapmi_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((m68ki_cpu.n_flag & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapge_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traplt_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapgt_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traple_16(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 2;
        if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traphi_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if (((!(m68ki_cpu.c_flag & 0x100)) && m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapls_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if (((m68ki_cpu.c_flag & 0x100) || (!m68ki_cpu.not_z_flag))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((!(m68ki_cpu.c_flag & 0x100))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapcs_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((m68ki_cpu.c_flag & 0x100)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapne_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if (m68ki_cpu.not_z_flag) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapeq_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((!m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvc_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((!(m68ki_cpu.v_flag & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapvs_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((m68ki_cpu.v_flag & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trappl_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((!(m68ki_cpu.n_flag & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapmi_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((m68ki_cpu.n_flag & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapge_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traplt_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if (((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapgt_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if (((!((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80)) && m68ki_cpu.not_z_flag)) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_traple_32(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        m68ki_cpu.pc += 4;
        if ((((m68ki_cpu.n_flag ^ m68ki_cpu.v_flag) & 0x80) || (!m68ki_cpu.not_z_flag))) {
            m68ki_exception_trap(7);
            return;
        }
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_trapv(void) {
    if ((!(m68ki_cpu.v_flag & 0x80))) {
        return;
    }
    m68ki_exception_trap(7);
}
static void m68k_op_tst_8_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xff);
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_ai(void) {
    uint res = OPER_AY_AI_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_pi(void) {
    uint res = OPER_AY_PI_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_pi7(void) {
    uint res = OPER_A7_PI_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_pd(void) {
    uint res = OPER_AY_PD_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_pd7(void) {
    uint res = OPER_A7_PD_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_di(void) {
    uint res = OPER_AY_DI_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_ix(void) {
    uint res = OPER_AY_IX_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_aw(void) {
    uint res = OPER_AW_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_al(void) {
    uint res = OPER_AL_8();
    m68ki_cpu.n_flag = (res);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_8_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCDI_8();
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_8_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCIX_8();
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_8_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = m68ki_read_imm_8();
        m68ki_cpu.n_flag = (res);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_16_d(void) {
    uint res = (((m68ki_cpu.dar[m68ki_cpu.ir & 7])) & 0xffff);
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_a(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = (sint16)(((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]));
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_16_ai(void) {
    uint res = OPER_AY_AI_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_pi(void) {
    uint res = OPER_AY_PI_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_pd(void) {
    uint res = OPER_AY_PD_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_di(void) {
    uint res = OPER_AY_DI_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_ix(void) {
    uint res = OPER_AY_IX_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_aw(void) {
    uint res = OPER_AW_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_al(void) {
    uint res = OPER_AL_16();
    m68ki_cpu.n_flag = ((res) >> 8);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_16_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCDI_16();
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_16_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCIX_16();
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_16_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = m68ki_read_imm_16();
        m68ki_cpu.n_flag = ((res) >> 8);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_32_d(void) {
    uint res = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_a(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_32_ai(void) {
    uint res = OPER_AY_AI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_pi(void) {
    uint res = OPER_AY_PI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_pd(void) {
    uint res = OPER_AY_PD_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_di(void) {
    uint res = OPER_AY_DI_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_ix(void) {
    uint res = OPER_AY_IX_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_aw(void) {
    uint res = OPER_AW_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_al(void) {
    uint res = OPER_AL_32();
    m68ki_cpu.n_flag = ((res) >> 24);
    m68ki_cpu.not_z_flag = res;
    m68ki_cpu.v_flag = 0;
    m68ki_cpu.c_flag = 0;
}
static void m68k_op_tst_32_pcdi(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCDI_32();
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_32_pcix(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = OPER_PCIX_32();
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_tst_32_i(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint res = m68ki_read_imm_32();
        m68ki_cpu.n_flag = ((res) >> 24);
        m68ki_cpu.not_z_flag = res;
        m68ki_cpu.v_flag = 0;
        m68ki_cpu.c_flag = 0;
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_unlk_32_a7(void) {
    (m68ki_cpu.dar + 8)[7] = m68ki_read_32_fc((m68ki_cpu.dar + 8)[7], m68ki_cpu.s_flag | 1);
}
static void m68k_op_unlk_32(void) {
    uint * r_dst = & ((m68ki_cpu.dar + 8)[m68ki_cpu.ir & 7]);
    (m68ki_cpu.dar + 8)[7] = * r_dst;
    * r_dst = m68ki_pull_32();
}
static void m68k_op_unpk_16_rr(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = (m68ki_cpu.dar[m68ki_cpu.ir & 7]);
        uint * r_dst = & (m68ki_cpu.dar[(m68ki_cpu.ir >> 9) & 7]);
        * r_dst = (( * r_dst) & ~0xffff) | (((((src << 4) & 0x0f00) | (src & 0x000f)) + m68ki_read_imm_16()) & 0xffff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_unpk_16_mm_ax7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = OPER_AY_PD_8();
        uint ea_dst;
        src = (((src << 4) & 0x0f00) | (src & 0x000f)) + m68ki_read_imm_16();
        ea_dst = ((m68ki_cpu.dar + 8)[7] -= 2);
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, (src >> 8) & 0xff);
        ea_dst = ((m68ki_cpu.dar + 8)[7] -= 2);
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, src & 0xff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_unpk_16_mm_ay7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = OPER_A7_PD_8();
        uint ea_dst;
        src = (((src << 4) & 0x0f00) | (src & 0x000f)) + m68ki_read_imm_16();
        ea_dst = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, (src >> 8) & 0xff);
        ea_dst = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, src & 0xff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_unpk_16_mm_axy7(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = OPER_A7_PD_8();
        uint ea_dst;
        src = (((src << 4) & 0x0f00) | (src & 0x000f)) + m68ki_read_imm_16();
        ea_dst = ((m68ki_cpu.dar + 8)[7] -= 2);
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, (src >> 8) & 0xff);
        ea_dst = ((m68ki_cpu.dar + 8)[7] -= 2);
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, src & 0xff);
        return;
    }
    m68ki_exception_illegal();
}
static void m68k_op_unpk_16_mm(void) {
    if (((m68ki_cpu.cpu_type) & ((0x00000008) | (0x00000010) | (0x00000040) | (0x00000020) | (0x00000200) | (0x00000080)))) {
        uint src = OPER_AY_PD_8();
        uint ea_dst;
        src = (((src << 4) & 0x0f00) | (src & 0x000f)) + m68ki_read_imm_16();
        ea_dst = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, (src >> 8) & 0xff);
        ea_dst = (--((m68ki_cpu.dar + 8)[(m68ki_cpu.ir >> 9) & 7]));
        m68ki_write_8_fc(ea_dst, m68ki_cpu.s_flag | 1, src & 0xff);
        return;
    }
    m68ki_exception_illegal();
}