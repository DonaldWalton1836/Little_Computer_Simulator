#include<iostream>

const int NumberMemory = 10;
const  int NumberRegister = 8;
const int MaxNumLabel = 65536;
const int MaxNumLength = 1000;

void printState(int memArr[NumberMemory], int regArr[NumberRegister], int PC);

using namespace std;

int main()
{
    int PC = 0;
    int IC = 0;

    int memArr[NumberMemory];
    int regArr[NumberRegister];


    for(int i = 0; i < NumberMemory; i++)
    {
        cin >> memArr[i];
    }
     for(int i = 0; i < NumberMemory; i++)
    {
        cout<<"mem["<<i<<"]="<<memArr[i]<<endl;
    }

    for(int i = 0; i < NumberRegister; i++)
    {
        regArr[i] = 0;
    }

    printState(memArr,regArr,PC);

    int opcode;
    
    bool runProgram = true;

        do
        {
            opcode = (memArr[PC] >> 22) &0x7;
            int regA = (memArr[PC] >> 19) & 0x7;
            int regB = (memArr[PC] >> 16) & 0x7;
            int destReg =(memArr[PC]>> 0) & 0x7;

            if(opcode == 0)
            {
                int ALU = regArr[regA] + regArr[regB];
                regArr[destReg] = ALU;

                printState(memArr,regArr,PC);

                PC++;
                IC++;
            }
            if(opcode == 1)
            {
                regArr[destReg] = regArr[regA] + regArr[regB];

                regArr[destReg] = ~regArr[destReg];
                PC++;
                IC++;
            }
            if(opcode == 2)
            {
                int offset = memArr[PC] & 0xFFFF;
                int signedEx = (offset & 0x8000) ? (offset | 0xFFFF0000):offset;
                int memADD = (regArr[regA] + signedEx) % NumberMemory;

                regArr[regB] = memArr[memADD];

                printState(memArr,regArr,PC);

                PC++;
                IC++;
            }
            if(opcode == 3)
            {
                int offset =  memArr[PC] & 0xFFFF;
                int signedEx = (offset & 0x8000) ? (offset | 0xFFFF0000):offset;
                int memADD = (memArr[regA] + signedEx) % 10;

                memArr[memADD] = regArr[regB];

                printState(memArr,regArr,PC);

                PC++;
                IC++;
            }
            if(opcode == 4)
            {
                int offset = memArr[PC] & 0xFFFF;
                int signedEx = (offset & 0x8000) ? (offset | 0xFFFF0000) : offset;

                if(memArr[regArr[regA]] == memArr[regArr[regB]])
                {
                    int branch = PC + 1 + signedEx;

                    printState(memArr,regArr,PC);
                    PC = branch;
                    IC++;
                    
                }
                else
                {
                    printState(memArr,regArr,PC);
                    PC++;
                    IC++;
                }

                
            }
            if(opcode == 5)
            {
                
                printState(memArr,regArr,PC);
            }
            if(opcode == 6)
            {
                
                PC++;
                IC++;
                runProgram = false;
                printState(memArr,regArr,PC);

                
            }
            if(opcode == 7)
            {
                printState(memArr,regArr,PC);
                PC++;
            }
        
        }while(opcode != 6);

        cout<<"Machine Halted"<<endl;
        cout<<"Total Instruction: "<<IC<<endl;
	    cout <<"Final state of machine: "<<endl;
	printState(memArr,regArr,PC);
    

    return 0;
}

void printState(int memArr[NumberMemory],int regArr[NumberRegister], int PC)
{
    cout<<"@@@"<<endl;
    cout<<"State: "<< PC<< endl;
    for(int i = 0; i < NumberMemory;i++)
    {
        cout<<"           mem["<<i<<"]="<<memArr[i]<<endl;

    }

    cout <<"Registers:"<<endl;
    cout <<endl;
    for(int i =0; i < NumberRegister; i++)
    {
        cout<<"         reg["<< i<<"]="<<regArr[i]<<endl;

        
    }
cout <<"End State:"<<endl;
}