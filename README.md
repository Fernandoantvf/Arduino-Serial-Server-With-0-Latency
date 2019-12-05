# Arduino-Serial-Server-With-0-Latency

Configures Serial Port to 0 Timeout and buffers received bytes until message is complete
Once 'CR' Char is received, it calls a function to process the complete message.

If a 'LF' Char is received or if buffer oveflows message buffer is cleared.
