<h1 align="center">Heroes New Tricks Mod</h1>
<p align="center"><img src="https://m2gaming.ca/wp-content/uploads/2024/03/Sonic-Heroes.jpg">

</p>

## About

This is a mod for Sonic Heroes that tweaks the moveset of the characters, it replaces and add new actions.

> [!CAUTION]
> This mod replaces Formation Changes to the d-pad left and right instead of Y and B, this is needed due to Heroes's lack of available buttons for custom moves.
> You can disable this in the mod config, but you won't be able to use all the custom moves such as Hammer Jump and Bounce in that case.

> [!NOTE]
> New Tricks now use the following dependencies:
> * [Sonic Heroes Action Expander](https://github.com/Sora-yx/SH-Action-Expander/releases)
> * [SH Essentials: Controller Hook](https://github.com/Sewer56/Heroes.Controller.Hook.ReloadedII/releases)


### Speed Type:
- SA1 Spin Dash (toggleable for each speed character) replace Rocket Accel.
- SA2 Bounce - Give Sonic and Amy the SA2 Bounce.

### Amy Exclusive:
- Propeller Tweaks - Increase duration and speed depending on your current speed level, you can also trigger it while falling to do some fancy speed combo.
- Tornado - Make Amy able to move when creating a Tornado mid air.
- Hammer Jump - Give her SA1 Hammer Jump back.


### Fly Type:
- Flight Tweaks - Make the fly duration and speed faster as your fly level rise


### Power Type
- Triangle Dive Tweaks - Duration increase as the power level rise, you can also trigger it while falling
- Wide Power Attack - Make Power characters able to move when firing Wide Power attack.


### Bonus:
- Add Chocola following Cheese once Team Rose is finished
- Add Amy's bird from SA1

Features are all optional, so you can toggle whatever you like.

That's pretty much it for now.

## How to install this Mod
- Get [Reloaded II](https://github.com/Reloaded-Project/Reloaded-II/releases/latest) if you don't have it already.
- Install and Open Reloaded II, then add a new game, select the executable of Sonic Heroes (Tsonic_win.exe) 
- Download this mod and put it in the ``Mods`` folder of Reloaded II
- Click on "Launch Application"

Enjoy!

## Build this Repo (For Programmers)

- Make sure Reloaded is installed with Heroes set up complete. (See previous section if not.)
- Install [Latest .NET SDK](https://dotnet.microsoft.com/en-us/download)
- Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) (During the install, make sure to check ``.NET Desktop Development`` and ``Desktop Developpment with C++``)
- Clone this repo and its submodules, easiest way is to use Git and type in a terminal ``git clone --recurse submodules https://github.com/Sora-yx/SH-New-Tricks.git`` if you don't have .git installed, [grab the Windows version here.](https://git-scm.com/install/windows) 
- Load the project from Visual Studio and use the Build menu to build the solution (make sure to select ``Release`` and ``x86`` as target first.
- Once the repo is build, check your ``mods`` folder of Reloaded, you should have a new folder named ``New_Tricks``, open it.
- Open the repo folder that you downloaded previously and look for the ``Mod Files`` folder, copy the ``Redirector`` folder and paste it in the ``New_Tricks`` folder.

All set. 



