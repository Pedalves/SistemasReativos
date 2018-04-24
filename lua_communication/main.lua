local mqtt = require("mqtt_library")

function mqttcb(topic, message)
   print("Received from topic: " .. topic .. " - message:" .. message)
   controle = not controle
end

function love.keypressed(key)
  mqtt_client:publish("apertou-tecla", key)
end

function love.load()
  controle = false
  mqtt_client = mqtt.client.create("test.mosquitto.org", 1883, mqttcb)
  mqtt_client:connect("cliente1412122e1320981")
  mqtt_client:subscribe({"1412122e1320981"})
end

function love.draw()
   if controle then
     love.graphics.rectangle("line", 10, 10, 200, 150)
   end
end

function love.update(dt)
  mqtt_client:handler()
end
  
