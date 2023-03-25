#include <detpic32.h>

typedef struct{
    char mem[100];  // Storage area
    int nchar;      // Number of characters to be transmitted
    int posrd;      // Position of the next character to be transmitted
} t_buf;


volatile t_buf txbuf;
void putstrInt(char *s);

int main(void){

    // Configure UART2: 115200, N, 8, 1
    // 1 - Configure BaudRate Generator
    U2BRG = 10;     //BaudRate = 115200 ->(20000000 / (16 * 115200)) - 1 = 10
    U2MODEbits.BRGH = 0;
    // 2 – Configure number of data bits, parity and number of stop bits(see U2MODE register)
    U2MODEbits.PDSEL = 0;   //00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;   //0 = 1 Stop bit
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;

    // Configure UART2 interrupts, with RX and TX interrupts DISABLED
    //disable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2TXIE = 0;
    IEC1bits.U2RXIE = 0;
    //set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 1;
    //define TX interrupt mode (UTXISEL bits)
    U2STAbits.UTXISEL = 1;

    // Enable global Interrupts
    EnableInterrupts();

    // Initialize buffer variable "nchar" with 0
    txbuf.nchar = 0;
    while(1){
    putstrInt("Test string which can be as long as you like as long as it is no longer than 100 characters\n");
    }
    return 0;
}

void _int_(32) isr_uart2(void)
{
    if (IFS1bits.U2TXIF == 1){
        if(txbuf.nchar > 0) {                       // At least one character to be transmitted
            U2TXREG = txbuf.mem[txbuf.posrd];       // Read 1 character from the buffer and send it
            
            // Update buffer "posrd" and "nchar" variables
            txbuf.posrd++;
            txbuf.nchar--;
        } else {
            // Disable UART2 Tx interrupts
            IEC1bits.U2TXIE = 0; 
        }
        // Clear UART2 Tx interrupt flag
        IFS1bits.U2TXIF = 0;
    }
}

void putstrInt(char *s){
    while(txbuf.nchar > 0); // Wait while the buffer is not empty
    // Copy all characters of the string "s" to the buffer
    while(*s != '\0') {
        txbuf.mem[txbuf.nchar] = *s;
        s++;
        txbuf.nchar++;
    }
    // Initialize "posrd" variable with 0
    txbuf.posrd = 0;
    // Enable UART2 Tx interrupts
    IEC1bits.U2TXIE = 1; 
}
