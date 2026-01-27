# TestosteroneGUI, Make Design Sigma Again
<p>TestosteroneGUI is graphical user interface written in C and SDL.</p>

## About Project
<p>In my adventure of game development and learning C, the topic of graphical stuffs have always been exiciting for me and so I created my own graphical interface.</p>
<p>When we consider the current status of programmers as obese creatures with colorful socks, the industry is becoming gay'er and we need to make programming masculine again. This is the very real purpose of project.</p>
<p>So that TestosteroneGUI has no aesthetic graphical design decisions.</p>
<p>For now it has only ability to render text and buttons with or without image.</p>
<p>If you want to have fancy widgets then make it and add pull request like a real man.</p>
<p>Since I considered rounded buttons as feminine, TestosteroneGUI has no rounded buttons. I think rounded buttons are feminine.</p>

## Dependencies
<p>This project uses SDL so that these C libraries must be installed:</p>
<ul>
    <li>sdl2</li>
    <li>sdl2_image</li>
    <li>sdl2_ttf</li>
</ul>

> Additionally you should keep a font file named `font.ttf` in directory in which this readme file is located.


## Compiling And Running
<p>Start compiling by running `make`.</p>
<p>It creates binary file named `run` when dependencies were met.</p>
<p>You can start using TestosteroneGUI by adding codes into `src/run.c` which is compiled above</p>

## Example
<p>This is an example code for blank page.</p>
<p>You can add this to `src/run.c`</p>

```c
#include "testo.h"

int main(){
    TESTO_Struct app = createTESTO("Example", 700, 500);
    initTESTO(&app);
    runTESTO(&app);
    clearTESTO(&app);
    return 0;
}
```

## Project Layout
<p>This diagramm demonstrates the general layout of the project.</p>
<img src="https://github.com/user-attachments/assets/0b4c5ef8-0648-43dd-aa8b-43bdcbc01fd2" width=500>

## Contribution
<p>Collaboration and Contributions are welcomed</p>
<p>Edit the project and add pull request</p>
