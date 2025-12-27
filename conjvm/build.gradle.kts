import com.adarshr.gradle.testlogger.theme.ThemeType

plugins {
    alias(libs.plugins.kotlin.jvm)
    alias(libs.plugins.kover)
    alias(libs.plugins.ktlint.gradle)
    alias(libs.plugins.test.logger)
    antlr
    `java-library`
}

tasks.generateGrammarSource {
    maxHeapSize = "64m"
    arguments = arguments + listOf(
        "-visitor",
        "-long-messages",
    )
    packageName = "org.erwinkok.conjvm"
}

repositories {
    mavenCentral()
}

dependencies {
    implementation(platform(kotlin("bom")))
    implementation(kotlin("stdlib"))

    implementation(libs.slf4j.api)
    implementation(libs.antlr.runtime)
    antlr(libs.antlr)

    runtimeOnly(libs.logback.classic)

    testImplementation(libs.junit.jupiter.api)
    testImplementation(libs.junit.jupiter.params)
    testImplementation(libs.slf4j.api)

    testRuntimeOnly(libs.logback.classic)
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
}

testlogger {
    theme = ThemeType.MOCHA
}

tasks.test {
    useJUnitPlatform()
}

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(21)
    }
}

kotlin {
    jvmToolchain(21)
}
