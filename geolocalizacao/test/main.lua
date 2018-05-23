local mqtt = require("/ext/mqtt_library")

function mqttcb(topic, message)
   print("Received from topic: " .. topic .. " - message:" .. message)
   controle = not controle
end

function love.keypressed(key)
  if key == 'a' then
    mqtt_client:publish("apertou-tecla", "a")
  end
end

function love.load()
  controle = false
  
  mqtt_client = mqtt.client.create("test.mosquitto.org", 1883, mqttcb)
  
  mqtt_client:connect("clientid 1320981")
  mqtt_client:subscribe({"puc-rio-inf1805"})
end

function love.draw()
   if controle then
     love.graphics.rectangle("line", 10, 10, 200, 150)
   end
end

function love.update(dt)
  mqtt_client:handler()
end
  