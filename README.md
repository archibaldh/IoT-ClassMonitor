# Classroom Monitor

## an IoT project

![App-Screenshot](public/assets/screenshot.png) <!--replace with screenshot of web interface-->

## How to use?
1. Open firmware\ws-dht11\arduino.ino in Arduino IDE and write it to your ESP32 (Make sure you read through the file to change details where the it asks you)
2. Open directory in your terminal ![Terminal Opening Project Folder](public/assets/open-folder.png)
3. Type 
    > node server.js  
    
    You should see something like this:
![Terminal Opening Project Folder](public/assets/node-serverjs.png)
4. Head to localhost:2467 in your web browser of choice, and you should see a screen similar to the screenshot shown at the start of this readme!

Now you can monitor your class through the web! 

### This didn't work! 
If you're new to node.js, (or interacting with ESP32s through node) this might not work for you. Follow the below steps
### Initializing a Node.js Environment

1. Ensure that Node.js and NPM are installed on your system:
    > node --version

    > npm --version

2. In terminal, inside the project directory:
    > npm init -y

3. This will add a package.json file

4. Install dependencies
    > npm install express ejs express-ejs-layouts

5. Install development dependencies
    > npm install --save-dev dotenv nodemon
### References:
 [Jetscholar/IoT-Weather](https://github.com/jetscholar/IoT-Weather)

Shoutout to fellow student Jun Lee for providing helping me out when unsure of how to do something.