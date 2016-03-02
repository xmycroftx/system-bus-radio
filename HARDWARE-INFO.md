Hardware Info
==============
This file details specific results people are experiencing with different hardware, settings, and frequencies.

Note: Thank you for testing this out! Are you using an antenna? At the beginning, I placed the antenna directly on top of the number 4 key and that worked best. It was a round antenna. Then once I knew it works I moved the antenna back. Moving it back reduced the number of frequencies that it worked on, and eventually only that one (1580 kHz) worked. Different hardware will certainly have different frequency response. Here are some results that have been sent in by readers. Please mail sbr@phor.net with your results or [edit this file directly ](https://github.com/fulldecent/system-bus-radio/edit/master/HARDWARE-INFO.md) and create a pull request.



| Tester                 | Transmitter                           | Receiver                        | Settings                      | Result                                                          |
| ---------------------- | ------------------------------------- | ------------------------------- | ----------------------------- | --------------------------------------------------------------- |
| William Entriken       | MacBook Air (13-inch, Early 2015)     | Sony STR-K670P, stock antenna   | 1580 kHz, `_mm_stream_si128`  | 2m open air, 1m thru drywall https://youtu.be/caGPmyMLYUI       |
| Scott Buchanan         | MacBook Pro Retina 15", early 2013    | N/A                             | N/A                           | Audible sound from computer https://goo.gl/ll3PxH               |
| Samuel Steele          | MacBook Air (13-inch, Mid-2013)       | Onkyo HT-R550, JVC Loop antenna | 1580 kHz, `_mm_stream_si128`  | Very clear at 2", only noise past 6"                            |
| Chris Smolinski        | MBP (??-inch, 2010)                   | netSDR, ??? antenna             | AM band, `_mm_stream_si128`   | No signal found anywhere on AM band                             |
| Chris Smolinski        | iMac (??-inch, 2015)                  | netSDR, ??? antenna             | AM band, `_mm_stream_si128`   | No signal found anywhere on AM band                             |
| Chris                  | ??? running Linux                     | Icom IC-R10, ??? antenna        | Busy loop, [linux port][1]    | Audible, noisy, not sure distance https://goo.gl/iAkOWV         |
| João Ventura           | MacBook Pro (15-inch, Late 2013)      | Tech Fuzzion, tele antenna      | 1600 kHz, `_mm_stream_si128`  | Few inches https://youtu.be/oXAeGZaka7o                         |
| Elvis Pfutzenreuter    | MacBook (12-inch, Early 2015)         | Sony ICF-SW11, internal antenna | 1580 kHz, `_mm_stream_si128`  | Up to 2m, recommends turning off mains & light                  |
| somini                 | Asus X201E, Linux                     | Clock radio, internal antenna   | 1580 kHz, `_mm_stream_si128`  | A few inches https://youtu.be/Nroc2BtO6NU                       |
| janka102               | MacBook Pro (15-inch, Early 2011)     | iHome iP90, included AM antenna | 1580 kHz, `_mm_stream_si128`  | Several inches https://youtu.be/qN9D3bxkbXk                     |
| Ryan Faerman           | MacBook Air (11-inch, 2014)           | Grundid Traveler 2 Digital, internal antenna | 1600 kHz         | ~6-8 inches                                                     |
| Ryou Ezoe              | Acer ASPIRE 5750, GNU/Linux           | Tecsun PL-310 fm/am Stereo World Band Dsp Receiver, internal antenna | 1440 kHz, [C++11 port][2] | 30 cm                          |
| Jeremy Zerfas          | MacBook Pro (15-inch, Mid 2012) 2.3   | Sony CFS-201 boom-box, internal antenna | Various AM channels   | Up to 6 feet                                                    |
| Jeremy Zerfas          | MacBook Pro (15-inch, Early 2008) 2.4 | Yamaha RX-V675, Loop antenna    | Various AM channels, `nanosleep` mod        | Up to 7 feet, definitely farther than Mid 2012 model w/ same rcvr |
| Jeremy Zerfas          |  2.8 GHz Athlon II X2 240, Gigabyte GA-MA785GM-US2H, Antec FusionRemote 350 HTPC case | Yamaha RX-V675, Loop antenna | Various AM channels, [linux port][3] | Up to 6" from the processor|

[1]: https://github.com/anfractuosity/system-bus-radio/blob/master/main.c
[2]: https://github.com/EzoeRyou/system-bus-radio/blob/master/main.cpp
[3]: https://github.com/fulldecent/system-bus-radio/pull/3
