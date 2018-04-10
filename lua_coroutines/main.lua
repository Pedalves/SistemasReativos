-- Renan da Fonte Simas dos Santos - 1412122
-- Pedro Ferreira - 1320981

function newblip (sec)
  local x, y = 0, 0
  
  return {
    update = coroutine.wrap (function (self)
      while 1 do
        local width, height = love.graphics.getDimensions( )
        x = x+5
        if x > width then
        -- volta para a esquerda da janela
          x = 0
        end
        wait(sec/100, self)
       
      end
    end),
    affected = function (pos)
      if pos>x and pos<x+10 then
      -- "pegou" o blip
        return true
      else
        return false
      end
    end,
    draw = function ()
      love.graphics.rectangle("line", x, y, 10, 10)
    end,
    sleep = 0,
    isActive = function(self)
      if(os.clock() >= self.sleep) then
        return true
      end
      return false
    end
  }
end

function newplayer ()
  local x, y = 0, 200
  local width, height = love.graphics.getDimensions( )
  return {
  try = function ()
    return x
  end,
  update = function (dt)
    x = x + 0.5
    if x > width then
      x = 0
    end
  end,
  draw = function ()
    love.graphics.rectangle("line", x, y, 30, 10)
  end
  }
end

function love.keypressed(key)
  if key == 'a' then
    pos = player.try()
    for i in ipairs(listabls) do
      local hit = listabls[i].affected(pos)
      if hit then
        table.remove(listabls, i) -- esse blip "morre" 
        return -- assumo que apenas um blip morre
      end
    end
  end
end

function love.load()
  player =  newplayer()
  listabls = {}
  for i = 1, 10 do
    listabls[i] = newblip(i)
  end
end

function love.draw()
  player.draw()
  for i = 1,#listabls do
    listabls[i].draw()
  end
end

function love.update(dt)
  player.update(dt)
  for i = 1,#listabls do
    if(listabls[i]:isActive()) then
      listabls[i]:update()      
    end
  end
end

function wait(segundos, meublip)
    cur = os.clock()
    meublip.sleep = cur+segundos
    coroutine.yield()

end
  
  
