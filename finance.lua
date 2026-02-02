-- Now, using Pallene, it become a high-performance module
local method = require("method") -- Loads the method.so compiled from Pallene

function calc_indicators(price, div) -- Must be global
    if price == 0.0 then return "<h1>Error: Price is zero</h1>" end
    local yield = method.calculate_yield(price, div)
    local ceiling = method.max_price_ceiling(div, 6.0)
    local status = (price <= ceiling) and "BUY" or "WAIT"
    local color = (status == "BUY") and "#27ae60" or "#e74c3c"

    -- Let's return a string of HTML
    return string.format([[
        <div style="font-family: Arial; border: 2px solid #333; padding: 20px; border-radius: 10px; max-width: 300px;">
            <h2 style="margin-top: 0;">BBAS3 Analysis</h2>
            <p><strong>Yield:</strong> R$ %.2f%%</p>
            <p><strong>Ceiling:</strong> R$ %.2f</p>
            <hr>
            <h3 style="color: %s; text-align: center;">STATUS: %s</h3>
        </div>
    ]], yield, ceiling, color, status)
end
