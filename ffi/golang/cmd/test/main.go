package main

import (
	"fmt"
	"log"

	"github.com/starpg/carbon"
)

func main() {
	c, err := carbon.Init("cmd/test/carbon.c14")
	if err != nil {
		log.Fatal(err)
	}
	defer c.Close()

	root, err := c.Fs().Root()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("fs root: ", root)

}
