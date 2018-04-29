use std::io::{stdout, stdin, Write};

fn get_integer(name: &str) -> i32 {
    let mut s = String::new();
    print!("{} : ", name);
    let _ = stdout().flush();
    stdin().read_line(&mut s).expect("ERR : Read");
    s.trim().parse::<i32>().expect("ERR : Cast")
}

fn main() {
    let (width, height, bnum) = (get_integer("width"), get_integer("height"), get_integer("bnum"));
}
