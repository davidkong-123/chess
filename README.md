<!-- TABLE OF CONTENTS -->



<!--Chess -->
### About The Project -- Chess



This is a chess game implemented in C++.

The game provide two modes for user: 

1. Human VS Human
2. Human VS AI (The AI has three levels of difficulty)


<img width="497" alt="chess_demo" src="https://user-images.githubusercontent.com/57188393/168458163-2fbff93a-e8a2-462f-a4f2-ed7db602f33b.png">

<img width="1097" alt="e19d418e79e98b3806d80c753d658ed" src="https://user-images.githubusercontent.com/57188393/168458681-316ac805-d5ed-49aa-88fd-4201375126eb.png">

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


<p align="right">(<a href="#top">back to top</a>)</p>
