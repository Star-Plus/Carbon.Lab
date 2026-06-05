package main

import (
	"fmt"
	"log"

	carbon "github.com/Star-Plus/Carbon.Lab/ffi/golang"
)

func main() {
	c, err := carbon.Init("carbon.c14")
	if err != nil {
		log.Fatal(err)
	}
	defer c.Close()

	root, err := c.Fs().Root()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("fs root: ", root)
	connection, err := c.Apps().Connect("test")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("app connection: ", connection)
}
