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