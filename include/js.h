String JS() {
    String script = "<script>"
    "let primaryColor;"
    "let random;"
    "let spiral;"
    "let spiralRandom;"
    "let Xmas;"
    "let clear;"
    "let range;"
    "let currentBrightness;"
    "let dot;"
    "const defaultColor = \"#0000ff\";"
    "var color;"
    "window.addEventListener(\"load\", startup, false);"
    "function startup() {"
        "primaryColor = document.querySelector(\"#primary\");"
        "primaryColor.value = defaultColor;"
        "primaryColor.addEventListener(\"change\", updatePrimary, false);"
        "random = document.querySelector(\"#random\");"
        "random.addEventListener(\"change\", setRandom, false);"
        "spiral = document.querySelector(\"#spiral\");"
        "spiral.addEventListener(\"change\", setSpiral, false);"
        "spiralRandom = document.querySelector(\"#spiralRandom\");"
        "spiralRandom.addEventListener(\"change\", setRandomSpiral, false);"
        "Xmas = document.querySelector(\"#Xmas\");"
        "Xmas.addEventListener(\"change\", setXmas, false);"
        "clear = document.querySelector(\"#clear\");"
        "clear.addEventListener(\"click\", clearLED, false);"
        "range = document.querySelector(\"#range\");"
        "range.addEventListener(\"click\", setBrightness, false);"
        "currentBrightness = document.querySelector(\"#currentBrightness\");"
        "dot = document.querySelector(\"#dot\");"
        "dot.addEventListener(\"click\", setDot, false);"
    "}"
    "function convert(hex){"
        "const r = parseInt(hex.substr(1, 2), 16);"
        "const g = parseInt(hex.substr(3, 2), 16);"
        "const b = parseInt(hex.substr(5, 2), 16);"
        "return [r,g,b]"
    "}"
    "function updatePrimary(event){"
        "Xmas.checked = false;"
        "random.checked = false;"
        "spiral.checked = false;"
        "spiralRandom.checked = false;"
        "let rgb = convert(event.target.value);"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/primary?r=\" + rgb[0] + \"&g=\" + rgb[1] + \"&b=\" + rgb[2] , false);"
        "req.send(null);"
    "}"
    "function setRandom(){"
        "Xmas.checked = false;"
        "spiral.checked = false;"
        "spiralRandom.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/random\" , false);"
        "req.send(null);"
    "}"
    "function setSpiral(){"
        "random.checked = false;"
        "Xmas.checked = false;"
        "spiralRandom.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/spiral\" , false);"
        "req.send(null);"
    "}"
    "function setXmas(){"
        "spiral.checked = false;"
        "random.checked = false;"
        "spiralRandom.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/xmas\" , false);"
        "req.send(null);"
    "}"
    "function clearLED(){"
        "Xmas.checked = false;"
        "random.checked = false;"
        "spiral.checked = false;"
        "spiralRandom.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/clear\" , false);"
        "req.send(null);"
    "}"
    "function setRandomSpiral(){"
        "Xmas.checked = false;"
        "random.checked = false;"
        "spiral.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/random_spiral\" , false);"
        "req.send(null);"
    "}"
    "function setDot(){"
        "Xmas.checked = false;"
        "random.checked = false;"
        "spiral.checked = false;"
        "spiralRandom.checked = false;"
        "let req = new XMLHttpRequest();"
        "req.open(\"GET\", \"http://192.168.50.98/dot\" , false);"
        "req.send(null);"
    "}"
    "function setBrightness(event){"
        "let req = new XMLHttpRequest();"
        "req.onreadystatechange = function() {"
            "currentBrightness.innerHTML = this.responseText;"
        "};"
        "req.open(\"GET\", \"http://192.168.50.98/brightness?b=\" + event.target.value , false);"
        "req.send(null);"
    "}"
    "</script>"    
    ;
    return script;
}