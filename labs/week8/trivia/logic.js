
function CheckOne(event)
{
    var trigger = event.srcElement;

    var outcome1 = document.querySelector("#outcome-1");
    var answer1 = document.querySelector("#answer-1");

    // Check if answer is correct
    if (trigger === answer1)
    {
        trigger.style.backgroundColor = 'green';
        outcome1.innerHTML = 'Correct!';
    }
    else
    {
        trigger.style.backgroundColor = 'red';
        outcome1.innerHTML = 'Incorrect';
    }
}

function CheckTwo(event)
{
    var answer = "29";

    var input = document.querySelector("#answer-2");

    var outcome2 = document.querySelector("#outcome-2");

    if (input.value === answer)
    {
        input.style.backgroundColor = 'green';
        outcome2.innerHTML = 'Correct!';
    }
    else
    {
        input.style.backgroundColor = 'red';
        outcome2.innerHTML = 'Incorrect';
    }


}