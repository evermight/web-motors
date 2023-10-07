const DISPLAY = {
   "ff":{"cls":"", "label":"&uarr;"},
   "fs":{"cls":"", "label":"&larr;"},
   "ss":{"cls":"", "label":"&#9632;"},
   "sf":{"cls":"", "label":"&rarr;"},
   "bb":{"cls":"", "label":"&darr;"},
   "bf":{"cls":"", "label":"&#9100;"},
   "ss":{"cls":"", "label":"&#9632;"},
   "fb":{"cls":"invert", "label":"&#9100;"}
};
var MQTT;
const fields = 'mqtt_server,mqtt_port,mqtt_topic,mqtt_user,mqtt_pass'.split(',');

const loadSettingsFromLocalStorage = () => {
  fields.forEach(item=>document.getElementById(item).value = localStorage.getItem(item));
}

const loadSettingsFromUrl = () => {
  const urlParams = new URLSearchParams(window.location.search);
  fields.forEach(field => {
    const param = urlParams.get(field);
    if(param) {
      document.getElementById(field).value = param;
    }
  });
}
const MQTTConnectSuccess = () => {
  document.querySelector('.direction-pad').classList.add('enable');
  document.querySelector('.settings').classList.remove('enable');

  fields
    .forEach(item=>localStorage.setItem(item,document.getElementById(item).value));
};
const MQTTConnect = () => {
  const host = document.getElementById("mqtt_server").value;
  const port = parseInt(document.getElementById("mqtt_port").value);
  const username = document.getElementById("mqtt_user").value;
  const password = document.getElementById("mqtt_pass").value;
  const cname="robo-"+Math.floor(Math.random() * 10000);

  MQTT = new Paho.MQTT.Client(host,port,cname);
  const options = {
    timeout: 3,
    onSuccess: MQTTConnectSuccess,
    userName:username,
    //useSSL: document.getElementById('mqtt_ssl').value === '1',
    useSSL: true,
    password,
  };
  MQTT.connect(options);
};
const btnPress = value => {
	const topic = document.getElementById("mqtt_topic").value;
	message = new Paho.MQTT.Message(value);
	message.destinationName = topic;
	MQTT.send(message);
}
/*
const btnPress = value => {
  fetch('./process.php?action='+value)
  .then(res => res.text())
  .then(res => setBtn(res))
}
*/
const setBtn = val => {
  document.querySelectorAll('[name=action]').forEach(btn=>btn.classList.remove('active'));
  const btn = document.querySelector('[name=action][value='+val+']').classList.add('active');
  if(btn) {
    btn.classList.add('active');
  }

  document.getElementById('current-action').innerHTML = DISPLAY[val].label;
  document.getElementById('current-action').className = DISPLAY[val].cls;
};
document.addEventListener('DOMContentLoaded', _ => {
  if(window.location.search.match(/debug=\d+/)) {
    document.getElementById('current-action').setAttribute('data-visible','1');
  }
  document.querySelectorAll('[name=action]').forEach(btn => {
    // If there are no other buttons pressed, then stop all actions
    btn.addEventListener('focusout', evt => {
      if(document.querySelectorAll('[name="action"]:focus').length < 1) {
        fetch('./process.php?action=ss')
        .then(res => res.text())
        .then(res => setBtn(res));
      }
    });
    btn.addEventListener('click', evt => btnPress(evt.currentTarget.value));
  });
  loadSettingsFromLocalStorage();
  loadSettingsFromUrl();
});
