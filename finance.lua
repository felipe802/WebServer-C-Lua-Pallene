-- The back (C) fetches the data very fast, and the front/logic (Lua) decides how to
-- display or process it.
function calculate_yield(price, dividend)
    local yield = (dividend / price) * 100
    return yield
end

print("Lua: Calculating stats for BBAS3...")