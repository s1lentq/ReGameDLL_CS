# ReGameDLL_CS [![Build Status](http://teamcity.rehlds.org/app/rest/builds/buildType:(id:ReGameDLLCs_Publish)/statusIcon)](http://teamcity.rehlds.org/viewType.html?buildTypeId=ReGameDLLCs_Publish&guest=1)
Reverse-engineered gamedll (mp.dll / Counter-Strike)

## What is this?
Regamedll_CS is a result of reverse engineering of original library mods HLDS (build 6153beta) using DWARF debug info embedded into linux version of HLDS, cs.so

## Goals of the project
* Provide more stable (than official) version of Counter-Strike game with extended API for mods and plugins

## How can use it?
Regamedll_CS is fully compatible with official mod CS 1.6 by Valve. All you have to do is to download binaries and replace original mo.dll/cs.so

Compiled binaries are available here: [link](http://nexus.rehlds.org/nexus/content/repositories/regamedll-snapshots/regamedll/regamedll/0.2-SNAPSHOT/)

Archive's bin directory contains 2 subdirectories, 'bugfixed' and 'pure'
* 'pure' version is designed to work exactly as official mod CS
* 'bugfixed' version contains some fixes and improvements

<b>Warning!</b> Regamedll_CS is not binary compatible with original hlds since it's compiled with compilers other than ones used for original mod CS. This means that plugins that do binary code analysis (Orpheu for example) probably will not work with Regamedll_CS.

## Configuration (cvars)
| CVar                          | Default | Min | Max          | Description                                    |
| :---------------------------- | :-----: | :-: | :----------: | :--------------------------------------------- |
| mp_freeforall                 | 0       | 0   | 1            | The style of gameplay where there aren't any teams (FFA mode)<br/>`0` disabled <br/>`1` enabled |
| mp_maxmoney                   | 16000   | 0   | `0x7FFFFFFF` | The maximum allowable amount of money in the game
| mp_round_infinite             | 0       | 0   | 1            | Flags for fine grained control (choose as many as needed)<br/>`0` disabled<br/>`1` enabled<br/><br/>or flags<br/>`a` block round time round end check<br/>`b` block needed players round end check<br/>`c` block VIP assassination/success round end check<br/>`d` block prison escape round end check<br/>`e` block bomb round end check<br/>`f` block team extermination round end check<br/>`g` block hostage rescue round end check<br/><br/>`Example setting:` "ae" blocks round time and bomb round end checks |
| mp_hegrenade_penetration      | 0       | 0   | 1            | Disable grenade damage through walls<br/>`0` disabled<br/>`1` enabled |
| mp_nadedrops                  | 0       | 0   | 2            | Drop a grenade after player death<br/>`0` disabled<br/>`1` drop one the grenade<br/>`2` drop a everyone grenades |
| mp_roundrespawn_time          | 20      | 0   | -            | Player cannot respawn until next round if more than N seconds has elapsed since the beginning round |
| mp_auto_reload_weapons        | 0       | 0   | 1            | Automatically reload each weapon on player spawn<br/>`0` disabled<br/>`1` enabled |
| mp_refill_bpammo_weapons      | 0       | 0   | 2            | Refill amount of backpack ammo up to the max <br/>`0` disabled<br/>`1` refill backpack ammo on player spawn<br/>`2` refill backpack ammo on each weapon reload |
| bot_deathmatch                | 0       | 0   | 1            | Set's the mode for the zBot <br/>`0` disabled<br/>`1` enable mode Deathmatch and not allow to do the scenario |
| mp_auto_join_team             | 0       | 0   | 1            | Automatically joins the team <br/>`0` disabled<br/>`1` enable (Use in conjunction with the cvar humans_join_team any/CT/T) |
| mp_max_teamkills              | 3       | 0   | -            | Maximum number of allowed teamkills before autokick. Used when enabled mp_autokick. |

## How to install zBot for CS 1.6?
* Extract all the files from an [archive](regamedll/extra/zBot/bot_profiles.zip?raw=true)
* Enter '-bots' option at the command line HLDS

## Build instructions
There are several software requirements for building rehlds:
<ol>
<li>Java Development Kit (JDK) 7+ (http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)</li>
<li>For Windows: Visual Studio 2013 and later</li>
<li>For Linux: Intel C++ Compiler 13 and later</li>
</ol>

### Checking requirements
####JDK version
Windows<pre>&gt; %JAVA_HOME%\bin\javac -version
javac 1.8.0_25
</pre>

Linux
<pre>$ javac -version
javac 1.7.0_65
</pre>

####Visual Studio
Help -> About

####ICC
<pre>$ icc --version
icc (ICC) 15.0.1 20141023
</pre>

### Building
On Windows:
<pre>gradlew --max-workers=1 clean buildRelease</pre>
* For faster building without unit tests use this:exclamation:
<pre>gradlew --max-workers=1 clean buildFixes</pre>

On Linux:
<pre>./gradlew --max-workers=1 clean buildRelease</pre>

* For faster building without unit tests use this:exclamation:
<pre>./gradlew --max-workers=1 clean buildFixes</pre>

Compiled binaries will be placed in the build/binaries/ directory

### Credits
Thanks to the project [ReHLDS](https://github.com/dreamstalker/rehlds) ( ReGameDLL_CS was created on the basis of ReHLDS )
