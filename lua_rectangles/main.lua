-- Renan da Fonte Simas dos Santos - 1412122
-- Pedro Ferreira - 1320981

-- renomear para main.lua

function naimagem (mx, my, x, y, w, h) 
  return (mx>x) and (mx<x+w) and (my>y) and (my<y+h)
end


function retangulo(x,y,w,h)
  local originalx, originaly, rx, ry, rw, rh = x, y, x, y, w, h
  return {
    draw = 
      function ()
        love.graphics.rectangle("line", rx, ry, rw, rh)
      end,
    keypressed =
      function (key)
        local mx, my = love.mouse.getPosition()
        if key == 'b' and naimagem (mx,my, rx, ry, rw, rh) then
           ry = 200
        end
        if key == "down" and naimagem(mx, my, rx, ry, rw, rh)  then
          ry = ry + 10
        end
        if key == "right" and naimagem(mx, my, rx, ry, rw, rh)  then
          rx = rx + 10
        end
      end,
    update =
      function(dt)
      end
  }
end

function love.load()
  r = {retangulo(50, 200, 200, 150), retangulo(50,50,100,100)}
end

function love.keypressed(key)
  for i = 1, #r do
    r[i].keypressed(key)
  end
end

function love.update (dt)
  local mx, my = love.mouse.getPosition()
end

function love.draw ()
  for i = 1, #r do
    r[i].draw()
  end
end
