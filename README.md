<!-- TABLE OF CONTENTS -->



<!--Chess -->
### About The Project -- Chess



This is a chess game implemented in C++.

The game provide two modes for user: 

1. Human VS Human
2. Human VS AI (The AI has three levels of difficulty)


<img width="497" alt="chess_demo" src="https://user-images.githubusercontent.com/57188393/168458163-2fbff93a-e8a2-462f-a4f2-ed7db602f33b.png">


### Game Demo

1. Human VS Human 



https://user-images.githubusercontent.com/57188393/168514534-cd429ac2-d2d6-48e7-80bf-694c7a81b639.mov

2. Human VS Computer level 1



https://user-images.githubusercontent.com/57188393/168514625-a434dfe1-3e57-4a33-ba28-0793f1e4d58f.mov





3. Human VS Computer level 2


https://user-images.githubusercontent.com/57188393/168514601-f8ef311d-5066-4f09-8b33-42546676792a.mov



4. HUman VS Computer level 3


https://user-images.githubusercontent.com/57188393/168514637-36f1cfd9-72e1-4572-b375-6eb704e6d27b.mov




### Built With

* C++
* Linux
* GDB
* GitLab

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->


### Installation

1. Clone the repo
   ```sh
   git clonehttps://github.com/davidkong-123/chess.git
   ```
2. make the Game
   ```sh
   cd src | make
   ```
   
   
### How to play

1. Initialize game
   ```sh
   ./chess
   ```
2. Select the Game Mode

   ``` game white-player black-player ``` starts a new game. The parameters white-player and black-player can be either human or computer[1-4].
   
   
3. A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved.



   For example: ``` move e2 e4```. Castling would specified by the two square move for the king: ```move e1 g1``` or ```move e1 c1``` for white. 

   Pawn promotion would additionally specify the piece type to which the pawn is promoted: ```move e7 e8 Q```. 

4.  Setup enters setup mode, within which you can set up your own initial board configurations.
This can only be done when a game is not currently running. Within setup mode, the following language is used:

   – + K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square, it is replaced. The board should be redisplayed.
   
   – - e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square, take no action. 
   
   – = colour makes it colour’s turn to go next. 
   
   – done leaves setup mode.


<p align="right">(<a href="#top">back to top</a>)</p>
