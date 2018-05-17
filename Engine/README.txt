Title: Rockbot

Mark Philipp
Andrew Valenzuela
Joseph Sesate
Omar Albulayhi

--------------
Considerations
--------------
The only consideration is that it is difficult to properly coordinate a project with 4 people who have conflicting schedules. 2 of our members have full-time jobs on top of being full-time students. These responsibilities create a lot of difficulty for organizing the group and properly delegating tasks and prioritizing features.

Thank you.

- Mark Philipp


---------------------------
Mouse and Keyboard Controls
---------------------------
You do not have to play the game using an xbox controller. Even though the graphics are catered to an Xbox controller, you can use mouse and keyboard to play the game. Here are the controls:

Left Shift = Start action input

Left-Click = X Button. Press this when the X Button icon shows and you will shoot a music note

Right-Click = B Button. Press this when the B Button icon shows and you'll shoot a note.

A = Move Left
D = Move Right
Space = Jump

Mouse movement = Aim. Your music notes fly towards your cursor when you fire them.

-------------
Level Creator
-------------
	---------------
	OBJECT CREATION
	---------------
	B = Create Background. When asked for filename, put in the name of the file + the extension
	
	M = create a platform / Model. When asked for filename, put in the name of the file + the extension
	
	P = create player.
	
	L = Create Next Level Trigger
	
	T = Create Text Trigger. NOTE: Text Triggers will not visibly show in game. They only show in level creator for your reference
	
	E = Create an enemy. You'll be asked the kind of enemy to create. Read the on screen menu for instructions
	
	H = Create health pack.

	----------------
	LOADING / SAVING
	----------------
	ENTER = Save Map. When asked for an input, use 0 - 9 to specify which level you are saving. (Level 1, 2, 3, etc.) ONLY put in the integer number, such as 1, 2, 3.
	
	Right Shift = Load Map. When asked for an input, use 0 - 9 to specify which level to load.

	NOTE: Levels in-game will be loaded sequentially. When you click "New Game", level 1 is loaded. If you touch the next level trigger in level 1,
	level 2 will be loaded, etc.

	-------------------
	OBJECT MANIPULATION
	-------------------
	+ / - on numpad = Scale Width of selected object up and down
	
	up arrow / down arrow = Scale height of selected object up and down.
	
	Left Click on an object = select the object.
	
	HOLD left click while an object is selected to move it around.
	
	Right click = deselect object
	
	DELETE = While an object is selected (highlighted in red), press delete to delete it

	--------------
	CAMERA OPTIONS
	--------------
	WASD = Move camera around in the scene
	
	Mouse Wheel = Zoom in and out

	-------------
	XML FILE INFO
	-------------
	XML Files are saved into <project folder>/LevelData. If you want to backup a level design for any reason, I recommend saving the xml file into a
	separate location for later use.

	--------------
	FILE PATH INFO
	--------------
	List of relative file paths for platforms, backgrounds, and level triggers. If you wish to download files from the internet and utilize them for textures,
	you'll want to save the files to these file paths to ensure they can be loaded and saved in the level creator properly.

	The below file paths are relative to your project location.

	Platforms = Images/Platforms
	Backgrounds = Images/Backgrounds
	NextLevelTrigger = Images/Misc