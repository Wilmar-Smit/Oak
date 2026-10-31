fn main() {
    let value: Option<&str> = Some("hello");

    // Clippy will fail here because unwrap() is explicitly denied
    let result = value.unwrap();

    println!("{}", result);
}
