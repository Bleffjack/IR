Inside the capture folder there are some test made pressing the original IR remote and recorded using a logic analyzer. In particular the software used to analyze
the signal was Saleae Logic Analyzer v2.3.35 . You can open the test using this software.

Useful link to understand the problem: https://www.youtube.com/watch?v=BUvFGTxZBG8&ab_channel=EEVblog

There's also an implementation for Arduino or ESP32 microcontrollers to turn Daikin AC from ON to OFF, it's rough but it works.


CURRENT WORK: 
From the capture on Mitsubishi it should be quite easy to analyze the signal ["reverse engineering"] and implement Mitsubishi version of the code.
