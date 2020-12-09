#include "exeInstr.h"


void execInstr(Instrct* instr, GPR* regs, int mem[])
{
    if(instr->oppcode == ADD)
    {
        int32_t res = regs->tReg[instr->rs] + regs->tReg[instr->rt];
        regs->tReg[instr->rd] = res;
    }
    else if (instr->oppcode == ADDI)
    {
        int32_t res = regs->tReg[instr->rs] + instr->imm;
        regs->tReg[instr->rt] = res;
    }
    else if (instr->oppcode == AND)
    {
        int32_t res = regs->tReg[instr->rs] & regs->tReg[instr->rt];
        regs->tReg[instr->rd] = res;
    }
    else if (instr->oppcode == BEQ)
    {
        if(instr->rs == instr->rt){
            regs->mReg.pc = regs->mReg.pc + instr->imm;
        }
    }
    else if (instr->oppcode == BGTZ)
    {
        if(instr->rs > 0){
            regs->mReg.pc = regs->mReg.pc + instr->imm;
        }
    }
    else if (instr->oppcode == BLEZ)
    {
        if(instr->rs <= 0){
            regs->mReg.pc = regs->mReg.pc + instr->imm;
        }
    }
    else if (instr->oppcode == BNE)
    {
        if(instr->rs != instr->rt){
            regs->mReg.pc = regs->mReg.pc + instr->imm;
        }
    }
    else if (instr->oppcode == DIV)
    {
        int q = regs->tReg[instr->rs] / regs->tReg[instr->rt];
        int m = regs->tReg[instr->rs] % regs->tReg[instr->rt];
        regs->mReg.lo = q;
        regs->mReg.hi = m;
    }
    else if (instr->oppcode == J && instr->type == 'J')
    {   
        regs->mReg.pc = instr->imm | (regs->mReg.pc & 0xF0000000);
    }
    else if (instr->oppcode == JAL)
    {
        /* code */
    }
    else if (instr->oppcode == JR)
    {
        /* code */
    }
    else if (instr->oppcode == LUI)
    {
        int32_t shift = regs->tReg[instr->rt];
        shift = shift << 16;
        regs->tReg[instr->rt] = shift;
    }
    else if (instr->oppcode == LW)
    {
        /* code */
    }
    else if (instr->oppcode == MFHI)
    {
        regs->tReg[instr->rd] = regs->mReg.hi;
    }
    else if (instr->oppcode == MFLO)
    {
        regs->tReg[instr->rd] = regs->mReg.lo;
    }
    else if (instr->oppcode == MULT)
    {
        int64_t res = regs->tReg[instr->rs] * regs->tReg[instr->rt];
        regs->mReg.lo = (int32_t)res;
        regs->mReg.hi = (int32_t)(res >> 32);
    }
    else if (instr->oppcode == OR)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] | regs->tReg[instr->rt];        
    }
    else if (instr->oppcode == ROTR && instr->rs != 0)
    {
        /* code */
    }
    else if (instr->oppcode == SLL) //ou instr->oppcode == NOP
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rt] << instr->imm;
    }
    else if (instr->oppcode == SLT)
    {
        if(regs->tReg[instr->rs] < regs->tReg[instr->rt]){
            regs->tReg[instr->rd] = 1;
        }else{
            regs->tReg[instr->rd] = 0;
        }
    }
    else if (instr->oppcode == SRL && instr->rs == 0)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rt] >> instr->imm;
    }
    else if (instr->oppcode == SUB)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] - regs->tReg[instr->rt];
    }
    else if (instr->oppcode == SW)
    {
        /* code */
    }
    else if (instr->oppcode == SYSCALL)
    {
        printf("This is a System Call");
    }
    else if (instr->oppcode == XOR)
    {
        regs->tReg[instr->rd] = regs->tReg[instr->rs] ^ regs->tReg[instr->rt];
    } 
}