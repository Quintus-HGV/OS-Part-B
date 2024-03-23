# OS-Part-B
<h2>Problem Statement</h2>

<p>Our project aims to implement a custom media centre operating system for the raspberry pi, tailored to improve media playback offering a refined user interface, and enhanced control mechanisms through a dedicated API, effectively applying essential operating system concepts and C programming skills </p>

<h2>Topic - Raspberry Pi OS Implementation: Custom Media Player</h2>

<h2>Introduction to the Problem</h2>
<p> Our aim for this project is to turn Raspberry Pi, a small and affordable computer, into a personalised media player like Netflix or Spotify, but for personal media collection. We will implement open source software such as Kodi or OSMC for personal media collection. On the other hand we will develop a separate application programming interface for media control as a dedicated Linux OS implementation</p>

<h3>Target OS environment: Linux (Preferably Ubuntu)</h3>

<h2>Useful tools:</h2>
<ul>
  <li>Download OSMC for Windows/MacOS/Linux: https://osmc.tv/download/</li>
  <li>OSMC setup: https://youtu.be/-9vgJ4u4saI?si=e1loVIyHLbvmiNU8</li>
</ul>

<h2>Steps to run on Linux</h2>
<h3>Note: Make sure the GCC compiler is installed in your system!</h3>
Step 1: Open terminal and install <b>libvlc</b> package using the command "sudo apt-get install libvlc-dev"<br>
Step 2: Install <b>pthread</b> package using command "sudo apt-get install libpthread-stubs0-dev"<br>
Step 3: Save the "main.c" file in a directory and open terminal there<br>
Step 4: Compile the main program and link the vlc and pthread libraries. Use command "gcc -o main main.c -lvlc -lpthread"<br>
Step 5: Run the executable by "./main"<br>
