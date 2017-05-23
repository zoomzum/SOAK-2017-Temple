//Please use the comand Show() instead of LEDS.show().  This will allow for code interruption after a set period in the case of an endless loop.
//Also, please try to avoid endless loops.  The calling function is set to repeat your sequence for 30 seconds, and it's the only sequence running, it will continue to repeat.
void SequenceA(){

  Show();
}

