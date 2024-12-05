fn main() {
    let search_term = "picture";
    let quote = "\
  Every face, every shop, bedroom window, public-house, and
  dark square is a picture feverishly turned--in search of what?
  It is the same with books.
  What do we seek through millions of pages?";

    for line in quote.lines() {
        if line.contains(search_term) {
            println!("{}", line);
        }
    }
}
