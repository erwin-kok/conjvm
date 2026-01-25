typedef signed int sint;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

typedef unsigned int uint;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef sint8 flag;
typedef sint8 int8;
typedef sint16 int16;
typedef sint32 int32;
typedef sint64 int64;

/* Helper to load a bitfield from EA */
typedef struct {
    uint32 field;

    /** When dealing with bitfields to/from memory,
     * we need to support offsets not aligned to a byte boundary.
     * Since the maximum width of a bitfield is 32, that means accessing at most
     * 5 bytes.
     * When writing back the result, we need to leave the bits outside the accessed
     * bitfield alone. To do that, we track the 5 bytes we read here
     */
    uint32 lo;
    uint8 hi;

} m68ki_bitfield_t;

typedef struct {
    uint cpu_type;     /* CPU Type: 68000, 68008, 68010, 68EC020, 68020, 68EC030, 68030, 68EC040, or 68040 */
    uint dar[16];      /* Data and Address Registers */
    uint dar_save[16];  /* Saved Data and Address Registers (pushed onto the
						   stack when a bus error occurs)*/
    uint ppc;		   /* Previous program counter */
    uint pc;           /* Program Counter */
    uint sp[7];        /* User, Interrupt, and Master Stack Pointers */
    uint vbr;          /* Vector Base Register (m68010+) */
    uint sfc;          /* Source Function Code Register (m68010+) */
    uint dfc;          /* Destination Function Code Register (m68010+) */
    uint cacr;         /* Cache Control Register (m68020, unemulated) */
    uint caar;         /* Cache Address Register (m68020, unemulated) */
    uint ir;           /* Instruction Register */
    floatx80 fpr[8];     /* FPU Data Register (m68030/040) */
    uint fpiar;        /* FPU Instruction Address Register (m68040) */
    uint fpsr;         /* FPU Status Register (m68040) */
    uint fpcr;         /* FPU Control Register (m68040) */
    uint t1_flag;      /* Trace 1 */
    uint t0_flag;      /* Trace 0 */
    uint s_flag;       /* Supervisor */
    uint m_flag;       /* Master/Interrupt state */
    uint x_flag;       /* Extend */
    uint n_flag;       /* Negative */
    uint not_z_flag;   /* Zero, inverted for speedups */
    uint v_flag;       /* Overflow */
    uint c_flag;       /* Carry */
    uint int_mask;     /* I0-I2 */
    uint int_level;    /* State of interrupt pins IPL0-IPL2 -- ASG: changed from ints_pending */
    uint stopped;      /* Stopped state */
    uint pref_addr;    /* Last prefetch address */
    uint pref_data;    /* Data in the prefetch queue */
    uint address_mask; /* Available address pins */
    uint sr_mask;      /* Implemented status register bits */
    uint instr_mode;   /* Stores whether we are in instruction mode or group 0/1 exception mode */
    uint run_mode;     /* Stores whether we are processing a reset, bus error, address error, or something else */
    int    has_pmmu;     /* Indicates if a PMMU available (yes on 030, 040, no on EC030) */
    int    pmmu_enabled; /* Indicates if the PMMU is enabled */
    int    fpu_just_reset; /* Indicates the FPU was just reset */
    uint reset_cycles;

    /* Clocks required for instructions / exceptions */
    uint cyc_bcc_notake_b;
    uint cyc_bcc_notake_w;
    uint cyc_dbcc_f_noexp;
    uint cyc_dbcc_f_exp;
    uint cyc_scc_r_true;
    uint cyc_movem_w;
    uint cyc_movem_l;
    uint cyc_shift;
    uint cyc_reset;

    /* Virtual IRQ lines state */
    uint virq_state;
    uint nmi_pending;

    /* PMMU registers */
    uint mmu_crp_aptr, mmu_crp_limit;
    uint mmu_srp_aptr, mmu_srp_limit;
    uint mmu_tc;
    uint16 mmu_sr;

    const uint8* cyc_instruction;
    const uint8* cyc_exception;

    /* Callbacks to host */
    int  (*int_ack_callback)(int int_line);           /* Interrupt Acknowledge */
    void (*bkpt_ack_callback)(unsigned int data);     /* Breakpoint Acknowledge */
    void (*reset_instr_callback)(void);               /* Called when a RESET instruction is encountered */
    void (*cmpild_instr_callback)(unsigned int, int); /* Called when a CMPI.L #v, Dn instruction is encountered */
    void (*rte_instr_callback)(void);                 /* Called when a RTE instruction is encountered */
    int  (*tas_instr_callback)(void);                 /* Called when a TAS instruction is encountered, allows / disallows writeback */
    int  (*illg_instr_callback)(int);                 /* Called when an illegal instruction is encountered, allows handling */
    void (*pc_changed_callback)(unsigned int new_pc); /* Called when the PC changes by a large amount */
    void (*set_fc_callback)(unsigned int new_fc);     /* Called when the CPU function code changes */
    void (*instr_hook_callback)(unsigned int pc);     /* Called every instruction cycle prior to execution */
} m68ki_cpu_core;

static inline uint EA_AY_AI_8(void);

static inline uint OPER_AY_AI_8(void)  {uint ea = EA_AY_AI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AY_AI_16(void) {uint ea = EA_AY_AI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AY_AI_32(void) {uint ea = EA_AY_AI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AY_PI_8(void)  {uint ea = EA_AY_PI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AY_PI_16(void) {uint ea = EA_AY_PI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AY_PI_32(void) {uint ea = EA_AY_PI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AY_PD_8(void)  {uint ea = EA_AY_PD_8();  return m68ki_read_8(ea); }
static inline uint OPER_AY_PD_16(void) {uint ea = EA_AY_PD_16(); return m68ki_read_16(ea);}
static inline uint OPER_AY_PD_32(void) {uint ea = EA_AY_PD_32(); return m68ki_read_32(ea);}
static inline uint OPER_AY_DI_8(void)  {uint ea = EA_AY_DI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AY_DI_16(void) {uint ea = EA_AY_DI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AY_DI_32(void) {uint ea = EA_AY_DI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AY_IX_8(void)  {uint ea = EA_AY_IX_8();  return m68ki_read_8(ea); }
static inline uint OPER_AY_IX_16(void) {uint ea = EA_AY_IX_16(); return m68ki_read_16(ea);}
static inline uint OPER_AY_IX_32(void) {uint ea = EA_AY_IX_32(); return m68ki_read_32(ea);}

static inline uint OPER_AX_AI_8(void)  {uint ea = EA_AX_AI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AX_AI_16(void) {uint ea = EA_AX_AI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AX_AI_32(void) {uint ea = EA_AX_AI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AX_PI_8(void)  {uint ea = EA_AX_PI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AX_PI_16(void) {uint ea = EA_AX_PI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AX_PI_32(void) {uint ea = EA_AX_PI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AX_PD_8(void)  {uint ea = EA_AX_PD_8();  return m68ki_read_8(ea); }
static inline uint OPER_AX_PD_16(void) {uint ea = EA_AX_PD_16(); return m68ki_read_16(ea);}
static inline uint OPER_AX_PD_32(void) {uint ea = EA_AX_PD_32(); return m68ki_read_32(ea);}
static inline uint OPER_AX_DI_8(void)  {uint ea = EA_AX_DI_8();  return m68ki_read_8(ea); }
static inline uint OPER_AX_DI_16(void) {uint ea = EA_AX_DI_16(); return m68ki_read_16(ea);}
static inline uint OPER_AX_DI_32(void) {uint ea = EA_AX_DI_32(); return m68ki_read_32(ea);}
static inline uint OPER_AX_IX_8(void)  {uint ea = EA_AX_IX_8();  return m68ki_read_8(ea); }
static inline uint OPER_AX_IX_16(void) {uint ea = EA_AX_IX_16(); return m68ki_read_16(ea);}
static inline uint OPER_AX_IX_32(void) {uint ea = EA_AX_IX_32(); return m68ki_read_32(ea);}

static inline uint OPER_A7_PI_8(void)  {uint ea = EA_A7_PI_8();  return m68ki_read_8(ea); }
static inline uint OPER_A7_PD_8(void)  {uint ea = EA_A7_PD_8();  return m68ki_read_8(ea); }

static inline uint OPER_AW_8(void)     {uint ea = EA_AW_8();     return m68ki_read_8(ea); }
static inline uint OPER_AW_16(void)    {uint ea = EA_AW_16();    return m68ki_read_16(ea);}
static inline uint OPER_AW_32(void)    {uint ea = EA_AW_32();    return m68ki_read_32(ea);}
static inline uint OPER_AL_8(void)     {uint ea = EA_AL_8();     return m68ki_read_8(ea); }
static inline uint OPER_AL_16(void)    {uint ea = EA_AL_16();    return m68ki_read_16(ea);}
static inline uint OPER_AL_32(void)    {uint ea = EA_AL_32();    return m68ki_read_32(ea);}
static inline uint OPER_PCDI_8(void)   {uint ea = EA_PCDI_8();   return m68ki_read_pcrel_8(ea); }
static inline uint OPER_PCDI_16(void)  {uint ea = EA_PCDI_16();  return m68ki_read_pcrel_16(ea);}
static inline uint OPER_PCDI_32(void)  {uint ea = EA_PCDI_32();  return m68ki_read_pcrel_32(ea);}
static inline uint OPER_PCIX_8(void)   {uint ea = EA_PCIX_8();   return m68ki_read_pcrel_8(ea); }
static inline uint OPER_PCIX_16(void)  {uint ea = EA_PCIX_16();  return m68ki_read_pcrel_16(ea);}
static inline uint OPER_PCIX_32(void)  {uint ea = EA_PCIX_32();  return m68ki_read_pcrel_32(ea);}


void x() {
    uint word2 = m68ki_read_imm_16();
    sint compare = m68ki_cpu.dar[(word2 >> 12) & 15] & 0xff;
    if (!((word2) & 0x00008000))
        compare = (int8) compare;
}