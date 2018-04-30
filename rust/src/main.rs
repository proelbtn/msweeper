extern crate rand;

mod msweeper;

use std::io::{stdout, stdin, Write};
use msweeper::Msweeper;

fn get_input<T>(name: &str) -> T where T: std::str::FromStr, <T as std::str::FromStr>::Err: std::fmt::Debug {
    loop {
        let mut s = String::new();
        print!("{} : ", name);
        let _ = stdout().flush();
        stdin().read_line(&mut s).expect("unknown error occured.");
        match s.trim().parse::<T>() {
            Ok(v) => return v,
            Err(_) => println!("Please input correctly")
        }
    }
}

fn display_map(ms: &Msweeper) {
    let w = ms.get_width();
    let h = ms.get_height();
    for y in 0..h {
        for x in 0..w {
            let (opened, num) = match ms.at(x, y) {
                Ok(val) => val,
                Err(_) => panic!("ERR : ms.at returned enexpected value.")
            };
            if !opened { print!("."); }
            else if num == 0 { print!(" "); }
            else { print!("{}", num); }
        }
        print!("\n");
    }
}

fn main() {
    let width: usize = get_input("width");
    let height: usize = get_input("height");
    let bnum: usize = get_input("bnum");
    
    let mut ms = Msweeper::new(width, height, bnum);

    while !ms.is_gameend() {
        display_map(&ms);
        let x: usize = get_input("X");
        let y: usize = get_input("Y");

        match ms.open(x, y) {
            Ok(_) => (),
            Err(_) => println!("width or height is not correct.")
        }
    }
}
