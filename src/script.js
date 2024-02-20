function enter(insertArr, dt) {
    const input = document.querySelector("div td input");
    const btn = document.querySelector('div td input[type="Button"]');

    const skip = document.querySelector("input[type='Button'][value='Skip Forward']")


    let idx = 0;

    let interval = setInterval(() => {
        if (idx > insertArr.length - 1) {
            clearInterval(interval)
            return
        }

        if (skip.disabled) {
            input.value = insertArr[idx++];
            btn.click()
        } else skip.click()
    }, dt)
}

function del(deleteArr, dt) {
    const input = document.querySelector("td:nth-child(3) input");
    const btn = document.querySelector('td:nth-child(4) input');

    const skip = document.querySelector("input[type='Button'][value='Skip Forward']")


    let idx = 0;

    let interval = setInterval(() => {
        if (idx > deleteArr.length - 1) {
            clearInterval(interval)
            return
        }

        if (skip.disabled) {
            input.value = deleteArr[idx++];
            btn.click()
        } else skip.click()
    }, dt)
}
