# ReGameDLL_CS
Reverse-engineered gamedll (mp.dll / Counter-Strike 1.6)

## What is this?
Regamedll_CS is a result of reverse engineering of original library mods HLDS (build 6153beta) using DWARF debug info embedded into linux version of HLDS, cs.so

At the moment, the work of reverse engineering continues

## Goals of the project
<ul>
<li>Provide more stable (than official) version of Half-Life dedicated server with extended API for mods and plugins</li>
</ul>

## How can use it?
At this stage we are working on the reverse engineering cs.so, so temporarily used library with hooks.
<ol>
<li>
You should rename your original a file in the root HLDS filesystem_stdio.dll/so to filesystem_stdio2.dll/so
</li>
<li>
Put a compiled binary a file filesystem_stdio.dll/so in the root HLDS
</li>
</ol>

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

On Linux:
<pre>./gradlew --max-workers=1 clean buildRelease</pre>

Compiled binaries will be placed in the build/binaries/ directory

### Credits
Thanks to the project [ReHLDS](https://github.com/dreamstalker/rehlds) ( ReGameDLL_CS was created on the basis of ReHLDS )
