# <a name="helloWorld"></a>**==== Hello World ====**

----

To begin, we are going to load an image and put it on the screen. Unlike other languages, Squirrel does not require code to be in a `main()` function like other C-like languages do, but if you feel it's cleaner, feel free to use one.

Let's start by making a variable to store our image in.

```
local image;
```

In Squirrel, `local` is the keyword used to declare a new variable. We can then assign this variable to any value we want, and even change the type of value at any time. For `image`, we will store a loaded image.

```
local image;
image = loadImage("res/ocean.png");
```

We're assuming here that your `ocean.png` file is in a folder called `res` for resources. It's good practice to keep your resources in a separate file so your main, or root, folder does not get cluttered. You can use the `res` folder found in `test`.

We can also assign a value to `image` as soon as it's declared, like so:

```
local image = loadImage("res/ocean.png");
```

You may be wondering why the file path for ocean.png uses a forward slash instead of a backslash. Windows is the only OS that uses backslashes for its paths, but it is also compatible with forward slashes, and other operating systems will usually only support forward, so it's best to always use them.

When you call the function `loadImage()`, it *returns* a value, meaning that the point where it was called becomes a value. For instance, if you typed `local x = mouseX();`, and the X position of the mouse was 42, it would be as though the code had been written `local x = 42;`. The semicolon at the end of each line says that the statement has ended and the system can move onto the next piece of code. Some languages will allow a line break to do the same, but if a language supports semicolons, then it's safer to use them. Currently, `image` has been assigned to a number, which is the number of ocean.png's index in XYG's memory. The image data itself is not stored in the variable. The reason why we don't store actual image data in the variable is so that muliple variables with the same value will not store copies of the image for each one.

Now that we have the image loaded, we can draw it to the screen. The function to do this is `drawImage()`. However, just calling this function will not make the window show the image. We need to call `update()` to make the screen refresh and show its contents. Add these two lines to the end:

```
drawImage(image, 0, 0);
update();
```

Run this code, and what do you see? It just blinked in and out, right? That's because computers take *everything* literally. It loaded the image, drew it, put it on screen, and said "I'm done," and quit. We have to tell it to keep the image up for a while. After `update()`, we use `wait()` to keep things as they are for a while. `wait()` counts how long it should wait in miliseconds, so to wait for a full second, we use a value of 1000. Our code should look like this now:

```
local image = loadImage("res/ocean.png");
drawImage(image, 0, 0);
update();
wait(1000);
```

And now you've written your first program in XYG! Yeah, it's not that much, but we'll be making more in later tutorials.