
#ifndef UTILS_H_
#define UTILS_H_
/*
 * retruns how many bits there are in guiadance command
 * @param name is the name of the command
 */

int getBits(char* name);

/*/
 * Check if a command is a guidance command
 * @param name is the command to be checked
 */


int isGuidance(char* name);

/*
 * returns the funct of given command
 * @param name is the name of the command
 */


int getFunct(char* name);



/*/
 * returns the Command Type of Instrucions
 * @param name is the instruction name
 */



char getType(char* name);

/*
 * reutrns the Opcode of instructions
 * @param name is the name of the instruction
 */


int getOpcode(char* name);
/*/
 * returns if the a number is out of boundry
 * @param num is the number to be checked
 */


/*
 * returns if a given command is instruction type
 * @param name is the name of the command
 */
int isInstruction(char* name);
/*
 * returns if a given command is guidance type
 * @param name is the name of the command
 */
int isGuidance(char* name);



#endif
