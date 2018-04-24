led1 = 3
led2 = 6
sw1 = 1
sw2 = 2

--pinos de leds são de saída
gpio.mode(led1, gpio.OUTPUT)
gpio.mode(led2, gpio.OUTPUT)

--apaga os leds
gpio.write(led1, gpio.LOW);
gpio.write(led2, gpio.LOW);

--pino de botão 1 por interrupção
--pullup garante sinal qdo não há algum
gpio.mode(sw1,gpio.INT,gpio.PULLUP)
gpio.mode(sw2,gpio.INT,gpio.PULLUP)
ledstate = false
speed = 1.0;
lastsw1 = 0;
lastsw2 = 0;
pinsturnedoff = false

--callback da interrupção
local function pincb(level, timestamp)
    --checa se os botoes foram pressionados
    if pinsturnedoff then
        gpio.write(led1, gpio.LOW);     
        return
    end

    ledstate =  not ledstate
    if ledstate then  
        gpio.write(led1, gpio.HIGH);
    else
    gpio.write(led1, gpio.LOW);
    end
end

--callback aumentar velocidade
local function speedupcb()
    --checa se os dois botões foram pressionados
    lastsw1 = tmr.now();
    if (lastsw1 - lastsw2 < 1000) then
        pinsturnedoff = true
    end

    speed = speed * 2.0;
    mytimer:stop();
    mytimer:register(1000/speed, tmr.ALARM_AUTO, pincb);
    mytimer:start();
end

--callback diminuir velocidade
local function speeddowncb()
    --checa se os dois botões foram pressionados
    lastsw2 = tmr.now();
    if (lastsw1 - lastsw2 < 1000) then
        pinsturnedoff = true
    end

    speed = speed / 2.0;
    mytimer:stop();
    mytimer:register(1000/speed, tmr.ALARM_AUTO, pincb);
    mytimer:start();
end

--registrar tratamento para botão
gpio.trig(sw1, "down", speedupcb)
gpio.trig(sw2, "down", speeddowncb)

mytimer = tmr.create()
mytimer:register(1000/speed, tmr.ALARM_AUTO, pincb);
mytimer:start()