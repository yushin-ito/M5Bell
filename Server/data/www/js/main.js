window.onload = () => {
  fetch(`http://${window.location.hostname}/api/log`, {
    method: "GET",
  })
    .then(async (response) => {
      if (!response.ok) {
        throw new Error();
      }
      addSystemLog("最終リクエスト", await response.text());
    })
    .catch((error) => {
      console.error("[error]", error);
    });
};

const ws = new WebSocket(`ws://${window.location.hostname}/ws`);

ws.onopen = () => {
  console.log("[ws] Connection established");
};

ws.onmessage = (event) => {
  const data = JSON.parse(event.data);
  console.log(`[ws] Get status code: ${data.code}`);
  switch (data.code) {
    case 0:
      addSystemLog("入室可能", data.timestamp);
      break;
    case 1:
      addSystemLog("入室不可能", data.timestamp);
      break;
    case 2:
      addSystemLog(`${data.count}分後対応可能`, data.timestamp);
      break;
    case 3:
      addSystemLog("入室リクエスト", data.timestamp);
      break;
  }
};

ws.onclose = (event) => {
  event.wasClean
    ? console.log(`[ws] Connection closed`)
    : console.log("[ws] Connection died");
};

ws.onerror = (error) => {
  console.log(`[error] ${error.message}`);
};

const onSubmit = () => {
  const params = {
    ssid: document.form.ssid.value,
    password: document.form.password.value,
  };
  const query = new URLSearchParams(params);
  fetch(`http://${window.location.hostname}/api/wifi?${query}`, {
    method: "GET",
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error();
      }
      console.log("Sent successfully");
    })
    .catch((error) => {
      console.error("[error]", error);
    });
  document.form.ssid.value = "";
  document.form.password.value = "";
  return true;
};

const onPress = () => {
  if (ws.readyState === 1) ws.send("request");
  else console.log("WebSocket not connected.");
};

const addSystemLog = (status, timestamp) => {
  const tbody = document.getElementById("tbody");
  const row = tbody.insertRow(-1);
  const cell1 = row.insertCell(0);
  const cell2 = row.insertCell(1);
  cell1.innerHTML = status;
  cell2.innerHTML = timestamp;
};
