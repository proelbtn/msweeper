extern crate rand;

mod msweeper;

use std::io::{stdout, stdin, Write};
use msweeper::Msweeper;

fn get_input<T>(name: &str) -> T where T: std::str::FromStr, <T as std::str::FromStr>::Err: std::fmt::Debug {
    let mut s = String::new();
    print!("{} : ", name);
    let _ = stdout().flush();
    stdin().read_line(&mut s).expect("ERR : Read");
    s.trim().parse::<T>().expect("ERR : Cast")
}

fn display_map(ms: &Msweeper) {
    let w = ms.get_width();
    let h = ms.get_height();
    for y in 0..h {
        for x in 0..w {
            print!("{}", ms.at(x, y));
        }
        print!("\n");
    }
}

fn main() {
    let width: usize = get_input("width");
    let height: usize = get_input("height");
    let bnum: usize = get_input("bnum");
    
    let ms = Msweeper::new(width, height, bnum);

    display_map(&ms);
}
