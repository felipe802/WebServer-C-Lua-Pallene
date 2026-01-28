-- finance.lua
function calculate_yield(price, dividend)
    local yield = (dividend / price) * 100
    return yield
end

print("Lua: Calculating stats for BBAS3...")