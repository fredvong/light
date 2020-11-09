const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>VKON LED Light Controller</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>
  <h2>VKON LED Light Controller</h2>
  <p>Fan Speed: <span id="textFanSpeed">%FANSPEED%</span> rpm</p>
  <p><span id="LEDSliderValue">%LEDSLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateLedSliderPWM(this)" id="ledPWMSlider" min="0" max="255" value="%LEDSLIDERVALUE%" step="1" class="slider"></p>
  <p><span id="FanSliderValue">%FANSLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateFanSliderPWM(this)" id="fanPWMSlider" min="0" max="255" value="%FANSLIDERVALUE%" step="1" class="slider"></p>
<script>

function updateLedSliderPWM(element) {
  var sliderValue = document.getElementById("ledPWMSlider").value;
  document.getElementById("LEDSliderValue").innerHTML = sliderValue;
  console.log("LED slider value:" + sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", "/led", true);
  //Send the proper header information along with the request
//  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhr.send("value="+sliderValue);
}

function updateFanSliderPWM(element, deviceNumber) {
  var sliderValue = document.getElementById("fanPWMSlider").value;
  document.getElementById("FanSliderValue").innerHTML = sliderValue;
  console.log("FAN slider value" + sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", "/fan", true);
  //Send the proper header information along with the request
//  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhr.send("value="+sliderValue);
}

window.onload = function() {
  function updateFanSpeed() {
    var myReqest = new XMLHttpRequest();
    myReqest.open("GET", "/fanspeed", true);
    myReqest.send();    
    myReqest.onreadystatechange = (e) => {
      document.getElementById("textFanSpeed").innerHTML = myReqest.responseText;
    }
  };
  setInterval(updateFanSpeed,1000);
}
</script>
</body>
</html>
)rawliteral";

const char config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>VKON LED Light Controller</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>
  <h2>VKON LED Light Controller</h2>
  <table>
     <th><td>Name</td><td>Value</td></th>
     <tr><td>version</td><td>%VERSION%</td></tr>
  </table>
</body>
</html>)rawliteral";
