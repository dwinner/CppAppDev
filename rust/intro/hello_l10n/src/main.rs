fn main() {
    greet_world();
}

fn greet_world() {
    println!("Hello, world!");

    let south_ger = "Grüß Gott!";
    let japan = "ハロー・ワールド";

    let regions = [south_ger, japan];

    for region in regions.iter() {
        println!("{}", &region);
    }
}
