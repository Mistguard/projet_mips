#include "exeInstr.h"

void execInstr(Instrct* instr, GPR* regs, int[] mem)
{
    if(strcmp(instr->opcode,"ADD") == 0)
    {
        int32_t res = instr->rs + instr->rt
        writeRegistrer(regs->tReg[rd], res);
    }
    else if (strcmp(instr->opcode,"ADDI") == 0)
    {
        int32_t res = instr->rs + instr->imm;
        writeRegistrer(regs->tReg[rt], res);
    }
    else if (strcmp(instr->opcode,"AND") == 0)
    {
        int32_t res = instr->rs & instr->rt
        writeRegistrer(regs->tReg[rd], res);
    }
    else if (strcmp(instr->opcode,"BEQ") == 0)
    {
        if(instr->rs == instr->rt){
            writeRegistrer(regs->tReg[pc], regs->tReg[pc]+instr->imm);
        }
    }
    else if (strcmp(instr->opcode,"BGTZ") == 0)
    {
        if(instr->rs > 0){
            writeRegistrer(regs->tReg[pc], regs->tReg[pc]+instr->imm);
        }
    }
    else if (strcmp(instr->opcode,"BLEZ") == 0)
    {
        if(instr->rs <= 0){
            writeRegistrer(regs->tReg[pc], regs->tReg[pc]+instr->imm);
        }
    }
    else if (strcmp(instr->opcode,"BNE") == 0)
    {
        if(instr->rs != instr->rt){
            writeRegistrer(regs->tReg[pc], regs->tReg[pc]+instr->imm);
        }
    }
    else if (strcmp(instr->opcode,"DIV") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"J") == 0)
    {
        writeRegistrer(regs->tReg[pc], instr->imm);
    }
    else if (strcmp(instr->opcode,"JAL") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"JR") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"LUI") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"LW") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"MFHI") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"MFLO") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"MULT") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"OR") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"ROTR") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SLL" && strcmp(instr->opcode,"NOP") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SLT") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SRL") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SUB") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SW") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"SYSCALL") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"XOR") == 0)
    {
        /* code */
    }
    else if (strcmp(instr->opcode,"ADD") == 0)
    {
        /* code */
    }
    
}