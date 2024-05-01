<!-- Title: Dev Log #1 -->
Hello, Hola. Welcome Welcome!

I wanted to make this video as the first in a series where I work on this little game I am making.

And yes if you read the title I will be doing it without a game engine.

During the series I want to explore engine concepts and other game dev related ideas and share my progress...

So to start, Here is dev log #1!

<!-- (Some intro here) -->
<!-- Intro -->

<!-- (Speed drawing / sketch of the game idea) -->
<!-- Speed drawing / sketch of the game idea -->
This project was meant to be a relatively simple game I could finish off in a couple of weeks.
It has been two as of writing this script.
So let's start by breaking down the game idea.

<!-- Game idea breakdown -->
Essentially I really really like rogue-likes. I also really like split screen co-ops.
<!-- Rogue-like and split screen co-op inspiration -->
Also while coming up with this idea Hell-Diver 2 had released and I HAVE BEEN WANTING TO GET MY HANDS ON THAT GAME.
But that's beside the point.
Also it is also inspired by Noita. Now I am not going to write a falling sand engine, but I did like their gameplay loop.

I really like their stratagem mechanic.

<!-- Stratagem mechanic explanation -->
This idea where you press a sequence of controls to summon something.
It was a really fun mechanic check.
<!-- Spells and mana explanation -->
I also like the idea that there isn't any limit on what spells you can cast, only your mana.
<!-- Knowledge check and learning spells from enemies -->
So I was like, let's also add a knowledge check where you literally learn spells from enemies.

<!-- Rogue-like dungeon crawler gameplay explanation -->
Outside of that gimmick, the game is essentially a rogue-like dungeon crawler.
You gather things from the dungeon, you find and kill the boss, and you move to the next level.

<!-- Goal: Go as far as you can -->
Go as far as you can.

Lets dive into the commit log!

So let's start by breaking down how I am even going to make this game.
I decided to use raylib-cpp
<!-- Show a image of raylib and raylib-cpp -->
<!-- Show a image of raylib and raylib-cpp -->
<!-- Display an image showcasing raylib and raylib-cpp -->
Raylib and raylib-cpp are quite litereally the backbone of the project.
These projects essentailly do all of the rendering and basic vecctor math etc for our project.

<!-- Display the simplicity of the code -->
These give us access to functions like these and OMG
Look at how simple this code is.
That is literally it for a simple window.

<!-- Explain the initial commits -->
Our first couple commits really didn't have much only a basic struct for a project.

!-- Show first window
