function changeCatImage()
{
    // Get the image element from the DOM
    let img = document.getElementById("cat-pic");

    // Find the current cat index from the src value
    const index = img.src.at(-5);
    
    // Increment the index by 1 (or wrap back if greater than 5)
    const newIndex = index % 5 + 1;

    // Set the src to the new index
    img.src = "cats/cat-" + newIndex + ".png";
}


function solve()
{
    alert("You solved the mystery!");
}