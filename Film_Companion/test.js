var term = "sample1";
var re = new RegExp("^([a-z0-9]{5,})$");
if (re.test(term)) {
    console.log("Valid");
} else {
    console.log("Invalid");
}