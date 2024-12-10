struct Counter {
    value: u64,
}

impl Counter {
    fn new() -> Self {
        Counter { value: 0 }
    }

    fn incr(&mut self) {
        self.value += 1;
    }
}

fn main() {
    let mut counter = Counter::new();

    counter.incr();
    counter.incr();

    println!("{}", counter.value);
}
