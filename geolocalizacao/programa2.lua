
http.post('https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyCj-JSZSFVOpRPkbfa-W3VNdfjeI_QKg5c',
  'Content-Type: application/json\r\n',
    [[
  {
  "wifiAccessPoints": [
      { "macAddress": "f4:6d:04:5d:75:bc" },
      { "macAddress": "f8:1a:67:a4:bc:80" },
      { "macAddress": "00:6b:f1:75:87:e0" },
      { "macAddress": "00:6b:f1:75:87:e1" },
      { "macAddress": "64:70:02:93:e4:44" },
      { "macAddress": "4e:66:41:be:09:4c" },
      { "macAddress": "e2:d0:12:82:fe:34" },
      { "macAddress": "f6:a3:3d:37:62:7b" },
      { "macAddress": "84:38:38:d7:00:ea" },
      { "macAddress": "62:45:cb:21:bd:41" },
      { "macAddress": "50:92:b9:09:d1:a2" },
      { "macAddress": "f2:81:7a:7e:ad:3e" }
    ]
  }
  ]]
,
  function(code, data)
    if (code < 0) then
      print("HTTP request failed :", code)
    else
      print(code, data)
    end
  end)
