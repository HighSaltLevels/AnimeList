# AnimeList

Thank you for taking a look at my Anime List program. It is still in progress, but you are free to look at it or try to compile it on your own machine.

A random goal that I had was to do all of my file handling using C libraries to avoid using file streams. File streams would have been a lot easier, but I wanted to keep up my C skills with file handling.

I have added an executable from compiling it on a 64bit debian based distro (Linux Mint 18.1 based on Ubuntu Xenial). I have also ran the binary on 64bit Fedora 29 and it ran with a bit a weird formatting. I will be adding an installer to compile the source on other operating systems when I get the chance. 

I did, however, throw together a quick bash script to move all of the files to the necessary locations. If you don't want to use that and you want to move the files to other locations, you will have to recompile on your own machine. The macros for the expected file locations are in file_handler.h and the macro names are pretty self explanatory. 

I have also compiled this on Windows and you will find the exe in the 7z file. Unfortunately, I'm still trying to get a windows installer to work and play nicely, but until then, you should be able to run the executable from the extracted folder. In addition to that, you can move it to C:\Program Files (x86)\AnimeList and create a desktop shortcut to there for easier access. 

Thanks again for taking a look at this project that I put together over a weekend and just decided to make on a whim.

