-- Now, using Pallene, it become a high-performance module
local method = require("method") -- Loads the method.so compiled from Pallene

function calc_indicators(price, div) -- Must be global
    if price == 0.0 then return 0.0, 0.0 end
    local yield = method.calculate_yield(price, div)
    local ceiling = method.max_price_ceiling(div, 6.0)
    return yield, ceiling
end
