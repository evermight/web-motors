#include <Arduino.h>
String html() {
  return "<!DOCTYPE html><html><head><style>form{margin-bottom: 50px; display: grid; grid-template: auto / 300px auto; grid-gap: 20px;}input, button, select{padding: 1em 0.5em;}form h1, form h2, form button{grid-column: 1/3;}</style><script>var fields='ss_id,ss_pass,api_url,mqtt_ssl,mqtt_server,mqtt_port,mqtt_topic,mqtt_user,mqtt_pass'.split(',');var fields_secret='ss_pass,mqtt_pass'.split(',');function printCurrentSettings(){fields.filter(item=>!fields_secret.includes(item)).forEach(item=>document.getElementById('val-'+item).innerHTML=localStorage.getItem(item)); fields_secret.forEach(item=>{document.getElementById('val-'+item).setAttribute('data-secret', localStorage.getItem(item)); document.getElementById('val-'+item).innerHTML=document.getElementById('val-'+item).getAttribute('data-mask');});}function preloadForm(){fields.forEach(item=>document.getElementById(item).value=localStorage.getItem(item));}function send(){fields.forEach(item=>localStorage.setItem(item, document.getElementById(item).value)); const body={}; fields.forEach(item=>{body[item]=document.getElementById(item).value}); fetch('/connect',{'headers':{'Content-Type':'application/json','Accept':'application/json'}, 'method':'post', 'body':JSON.stringify(body)}) .then(r=>r.json()) .then(r=>{fields .filter(item=>r.hasOwnProperty(item)) .forEach(item=>localStorage.setItem(item,r[item]));}); printCurrentSettings();}document.addEventListener('DOMContentLoaded',()=>{preloadForm(); printCurrentSettings();});</script></head><body> <form> <h1>Connect with:</h1> <label>SSID</label><input id=\"ss_id\"/> <label>PASS</label><input id=\"ss_pass\" type=\"password\"/> <label>MQTT_SSL</label><select id=\"mqtt_ssl\"><option value=\"1\">Enable Encryption</option><option value=\"0\">Disable Encryption</option></select> <label>MQTT_SERVER</label><input id=\"mqtt_server\" type=\"url\"/> <label>MQTT_PORT</label><input id=\"mqtt_port\" type=\"number\"/> <label>MQTT_TOPIC</label><input id=\"mqtt_topic\"/> <label>MQTT_USER</label><input id=\"mqtt_user\"/> <label>MQTT_PASS</label><input id=\"mqtt_pass\" type=\"password\"/> <label>API_URL</label><input id=\"api_url\" type=\"url\"/> <button type=\"button\" onClick=\"send();\">Save</button> </form> <form> <h2>Current Settings</h2> <label>SSID</label><span id=\"val-ss_id\"></span> <label>PASS</label><span id=\"val-ss_pass\" data-secret=\"\" data-mask=\"***click to show***\" onClick=\"this.innerHTML=this.getAttribute('data-secret')\"></span> <label>MQTT_SSL</label><span id=\"val-mqtt_ssl\"></span> <label>MQTT_SERVER</label><span id=\"val-mqtt_server\"></span> <label>MQTT_PORT</label><span id=\"val-mqtt_port\"></span> <label>MQTT_TOPIC</label><span id=\"val-mqtt_topic\"></span> <label>MQTT_USER</label><span id=\"val-mqtt_user\"></span> <label>MQTT_PASS</label><span id=\"val-mqtt_pass\" data-secret=\"\" data-mask=\"***click to show***\" onClick=\"this.innerHTML=this.getAttribute('data-secret')\"></span> <label>API_URL</label><span id=\"val-api_url\"></span> </form></body></html>";
}
// Minify this and escape double quotes
/*
<!DOCTYPE html>
<html>
<head>
<style>
  form {margin-bottom: 50px; display: grid; grid-template: auto / 300px auto; grid-gap: 20px;}
  input, button, select {padding: 1em 0.5em;}
  form h1, form h2, form button {grid-column: 1/3;}
</style>
<script>
var fields = 'ss_id,ss_pass,api_url,mqtt_ssl,mqtt_server,mqtt_port,mqtt_topic,mqtt_user,mqtt_pass'.split(',');
var fields_secret = 'ss_pass,mqtt_pass'.split(',');

function printCurrentSettings() {
  fields.filter(item=>!fields_secret.includes(item)).forEach(item=>document.getElementById('val-'+item).innerHTML = localStorage.getItem(item));
  fields_secret.forEach(item=>{
    document.getElementById('val-'+item).setAttribute('data-secret', localStorage.getItem(item));
    document.getElementById('val-'+item).innerHTML = document.getElementById('val-'+item).getAttribute('data-mask');
  });
}
function preloadForm() {
  fields.forEach(item=>document.getElementById(item).value = localStorage.getItem(item));
}
function send() {
  fields.forEach(item=>localStorage.setItem(item, document.getElementById(item).value));

  const body = {};
  fields.forEach(item=>{body[item] = document.getElementById(item).value});

  fetch('/connect',{
    'headers':{'Content-Type':'application/json','Accept':'application/json'},
    'method':'post',
    'body':JSON.stringify(body)
  })
  .then(r=>r.json())
  .then(r=>{
    fields
      .filter(item=>r.hasOwnProperty(item))
      .forEach(item=>localStorage.setItem(item,r[item]));
  });

  printCurrentSettings();
}

document.addEventListener('DOMContentLoaded',()=>{
  preloadForm();
  printCurrentSettings();
});
</script>
</head>
<body>
  <form>
    <h1>Connect with:</h1>
    <label>SSID</label><input id="ss_id" />
    <label>PASS</label><input id="ss_pass" type="password" />
    <label>MQTT_SSL</label><select id="mqtt_ssl"><option value="1">Enable Encryption</option><option value="0">Disable Encryption</option></select>
    <label>MQTT_SERVER</label><input id="mqtt_server" type="url"/>
    <label>MQTT_PORT</label><input id="mqtt_port" type="number" />
    <label>MQTT_TOPIC</label><input id="mqtt_topic" />
    <label>MQTT_USER</label><input id="mqtt_user" />
    <label>MQTT_PASS</label><input id="mqtt_pass" type="password" />
    <label>API_URL</label><input id="api_url" type="url" />
    <button type="button" onClick="send();">Save</button>
  </form>
  <form>
    <h2>Current Settings</h2>
    <label>SSID</label><span id="val-ss_id"></span>
    <label>PASS</label><span id="val-ss_pass" data-secret="" data-mask="***click to show***" onClick="this.innerHTML = this.getAttribute('data-secret')"></span>
    <label>MQTT_SSL</label><span id="val-mqtt_ssl"></span>
    <label>MQTT_SERVER</label><span id="val-mqtt_server"></span>
    <label>MQTT_PORT</label><span id="val-mqtt_port"></span>
    <label>MQTT_TOPIC</label><span id="val-mqtt_topic"></span>
    <label>MQTT_USER</label><span id="val-mqtt_user"></span>
    <label>MQTT_PASS</label><span id="val-mqtt_pass" data-secret="" data-mask="***click to show***" onClick="this.innerHTML = this.getAttribute('data-secret')"></span>
    <label>API_URL</label><span id="val-api_url"></span>
  </form>
</body>
</html>

*/
